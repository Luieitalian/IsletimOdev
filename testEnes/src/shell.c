#include "shell.h"

// Komut istemini yazdırır ve kullanıcıdan giriş alır
void prompt() {
    printf("> ");
    fflush(stdout); // Output buffer'ı temizler
}

// Komutu çalıştırır
void execute_command(char *command) {
    pid_t pid = fork(); // Yeni bir alt süreç oluşturur

    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) { // Çocuk süreç
        char *args[100];
        parse_command(command, args);

        // Built-in komutları kontrol et
        handle_builtin_commands(args);

        // Eğer yönlendirme varsa, işleme devam et
        if (handle_input_redirection(args) || handle_output_redirection(args)) {
            return;
        }

        // Pipe komutları varsa, işlemi gerçekleştir
        if (strchr(command, '|')) {
            execute_pipe_commands(args);
        }

        // Eğer komut bir dış programsa, execv ile çalıştırılır
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(1);
    } else { // Ebeveyn süreç
        if (!is_background_command(command)) {
            waitpid(pid, NULL, 0); // Çocuğun tamamlanmasını bekler
        }
    }
}

// Komutları ve argümanlarını ayırır
void parse_command(char *input, char **args) {
    char *token = strtok(input, " \t\n");
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " \t\n");
        i++;
    }
    args[i] = NULL; // Sonlandırıcı ekler
}

// Built-in komutları işler
void handle_builtin_commands(char **args) {
    if (args[0] == NULL) {
        return; // Eğer hiç komut yoksa, bir şey yapma
    }

    if (strcmp(args[0], "quit") == 0) {
        quit_shell();
        exit(0); // quit komutu alındığında shell kapanır
    }
}

// Giriş yönlendirmesini kontrol eder ve uygular
int handle_input_redirection(char **args) {
    int i = 0;
    int input_fd;

    // Komutları tarar ve '<' işaretini bulursa yönlendirme yapar
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            input_fd = open(args[i + 1], O_RDONLY);
            if (input_fd == -1) {
                perror("Giriş dosyası bulunamadı");
                return 1;
            }

            dup2(input_fd, STDIN_FILENO); // stdin yönlendirilir
            close(input_fd);
            args[i] = NULL; // Komuttan sonra gelen kısmı sonlandırır
            return 1;
        }
        i++;
    }
    return 0;
}

// Çıkış yönlendirmesini kontrol eder ve uygular
int handle_output_redirection(char **args) {
    int i = 0;
    int output_fd;

    // Komutları tarar ve '>' işaretini bulursa yönlendirme yapar
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            output_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd == -1) {
                perror("Çıkış dosyası açılamadı");
                return 1;
            }

            dup2(output_fd, STDOUT_FILENO); // stdout yönlendirilir
            close(output_fd);
            args[i] = NULL; // Komuttan sonra gelen kısmı sonlandırır
            return 1;
        }
        i++;
    }
    return 0;
}

// Boru (pipe) komutlarını çalıştırır
void execute_pipe_commands(char **args) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0) { // İlk süreç (komut 1)
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else { // İkinci süreç (komut 2)
        pid2 = fork();
        if (pid2 == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            execvp(args[2], &args[2]);
            perror("execvp");
            exit(1);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
}

// Arka planda çalışan komutları işler
void handle_background_process(char *command) {
    pid_t pid = fork();

    if (pid == 0) {
        // Arka planda çalıştırmak için komutları işle
        char *args[100];
        parse_command(command, args);
        execvp(args[0], args);
        exit(1);
    }
}

// Arka plan komutunu kontrol eder
int is_background_command(char *command) {
    if (command[strlen(command) - 1] == '&') {
        command[strlen(command) - 1] = '\0'; // '&' karakterini komuttan çıkarır
        return 1;
    }
    return 0;
}

// quit komutunu işler
void quit_shell() {
    printf("Kabuk sonlandırılıyor...\n");
}

#include "pipe.h"

// Pipe komutlarını işler
void handle_pipe(char *input) {
    char *args[100];
    int num_pipes = 0;

    // Komutları ayırarak boruları tanımlar
    char *command = strtok(input, "|");
    while (command != NULL) {
        args[num_pipes] = command;
        num_pipes++;
        command = strtok(NULL, "|");
    }

    execute_pipe_commands(args, num_pipes); // Boru komutlarını çalıştırır
}

// Boru komutlarını çalıştırır
void execute_pipe_commands(char **args, int num_pipes) {
    int i;
    int pipefds[2 * (num_pipes - 1)]; // Pipe dosya tanımlayıcıları
    pid_t pid;

    // Boruların oluşturulması
    for (i = 0; i < num_pipes - 1; i++) {
        if (pipe(pipefds + i * 2) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Komutları çalıştır
    for (i = 0; i < num_pipes; i++) {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) { // Çocuk süreç
            // İlk komutun girdisini düzenle
            if (i > 0) {
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO); // Önceki komutun çıktısını al
            }

            // Son komutun çıktısını düzenle
            if (i < num_pipes - 1) {
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO); // Gelecek komuta yönlendir
            }

            // Boru dosya tanımlayıcılarını kapat
            close_pipes(pipefds, num_pipes);

            // Komutları çalıştır
            char *args_for_command[100];
            parse_command(args[i], args_for_command);
            if (execvp(args_for_command[0], args_for_command) == -1) {
                perror("execvp");
                exit(1);
            }
        }
    }

    // Ebeveyn süreç, tüm çocuk süreçlerin bitmesini bekler
    for (i = 0; i < num_pipes; i++) {
        wait(NULL);
    }

    // Boru dosya tanımlayıcılarını kapat
    close_pipes(pipefds, num_pipes);
}

// Boru dosya tanımlayıcılarını kapatır
void close_pipes(int *pipefds, int num_pipes) {
    int i;
    for (i = 0; i < 2 * (num_pipes - 1); i++) {
        close(pipefds[i]);
    }
}

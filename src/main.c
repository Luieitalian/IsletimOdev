#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

// Girişi komut ve argümanlara bölme
void input_dividing(char *input, char **args) {
    char *token;
    int i = 0;

    token = strtok(input, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the argument list
}

int main() {
    char input[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        // Display prompt
        printf("> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Girilen okunamadı!");
            continue;
        }

        // girişi komut ve argümanlara böl
        input_dividing(input, args);

        // komut için fork
        pid = fork();
        if (pid < 0) {
            perror("Fork başarısız");
            continue;
        }

        if (pid == 0) {
            // Çocuk proseste çalıştır
            if (execvp(args[0], args + 1) == -1) {  // ilk args[0] komut iken diğerleri args + 1 argümanlar
                perror("Komutu çalıştırma başarısız");
                exit(1);
            }
        } else {
            // Çocuk prosesin bitimini bekle
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

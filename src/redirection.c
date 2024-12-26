#include "shell.h"

void yonlendirme_handle(char **args, int *arg_count) {
    char *input_file = NULL;
    char *output_file = NULL;
    int new_arg_count = 0;
    
    // Yönlendirme sembollerini ara ve dosya isimlerini kaydet
    for (int i = 0; i < *arg_count; i++) {
        if (strcmp(args[i], "<") == 0 && i + 1 < *arg_count) {
            input_file = args[i + 1];
            i++;
        } else if (strcmp(args[i], ">") == 0 && i + 1 < *arg_count) {
            output_file = args[i + 1];
            i++;
        } else {
            args[new_arg_count++] = args[i];
        }
    }
    args[new_arg_count] = NULL;
    *arg_count = new_arg_count;

    if (input_file) {
        int fd = open(input_file, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Giriş dosyası bulunamadı: %s\n", input_file);
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (output_file) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Çıkış dosyası açılamadı");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
} 
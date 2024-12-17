#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100
#define MAX_ARG_COUNT 20

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_COUNT];  // Argümanların tutacağı dizi
    int arg_count;

    while (1) {
        // Kullanıcıdan komut al
        printf("> ");
        fflush(stdout);
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            continue;
        }

        // Girdinin sonundaki '\n' karakteri temizlenir
        input[strcspn(input, "\n")] = '\0';

        // Çıkış komutu kontrol edilir
        if (strcmp(input, "exit") == 0) {
            printf("Programdan çıkılıyor...\n");
            break;
        }

        // Argümanları temizle
        memset(args, 0, sizeof(args));
        arg_count = 0;

         // Komut ve argümanları ayrıştır
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAX_ARG_COUNT) {
            args[arg_count++] = token;  // Argümanları diziye kaydet
            token = strtok(NULL, " ");
        }

         // Argümanları listele
        if (arg_count > 0) {
            printf("Komut: %s\n", args[0]);
            for (int i = 1; i < arg_count; i++) {
                printf("Argüman %d: %s\n", i, args[i]);
            }
        }

         // Komutlara göre işlem yap
        if (strcmp(args[0], "help") == 0) {
            printf("Kullanılabilir komutlar: help, exit, echo\n");
        } else if (strcmp(args[0], "echo") == 0) {
            printf("Echo: ");
            for (int i = 1; i < arg_count; i++) {
                printf("%s ", args[i]);
            }
            printf("\n");
        } else {
            printf("Bilinmeyen komut: %s\n", args[0]);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        // Prompt göster
        printf("> ");
        fflush(stdout);  // Prompt'un hemen ekranda görünmesini sağlar

        // Kullanıcıdan girdi al
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\nÇıkılıyor...\n");
            break;
        }

        // Girdinin sonundaki '\n' karakterini temizle
        input[strcspn(input, "\n")] = '\0';

        // Çıkış komutunu kontrol et
        if (strcmp(input, "exit") == 0) {
            printf("Programdan çıkılıyor...\n");
            break;
        }

        // Komutu işleme
        printf("Girdiğiniz komut: %s\n", input);

        // Burada komuta göre işlem yapabilirsin
    }

    return 0;
}

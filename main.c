#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256 
// Maximum girdi sayısı tanımlanır

int main() {
    char input[MAX_INPUT_SIZE]; // Maximum girdi sayısı için liste oluşturulur

    while (1) {
        // Prompt gösterilir
        printf("> ");
        fflush(stdout);  // Prompt'un hemen ekranda görünmesi sağlanır

        // Kullanıcıdan girdi alınır
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\nÇıkılıyor...\n");
            break;
        }

        // Girdinin sonundaki '\n' karakteri temizlenir
        input[strcspn(input, "\n")] = '\0';

        // Çıkış komutu kontrol edilir
        if (strcmp(input, "exit") == 0) {
            printf("Programdan çıkılıyor...\n");
            break;
        }

        // Komutu işlenir
        printf("Girdiğiniz komut: %s\n", input);
    }

    return 0;
}

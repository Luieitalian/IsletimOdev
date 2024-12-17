#include "../include/test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 100
#define MAX_ARG_COUNT 20

int main() {
  char input[MAX_INPUT_SIZE];
  char *args[MAX_ARG_COUNT]; // Argümanların tutacağı dizi
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
      args[arg_count++] = token; // Argümanları diziye kaydet
      token = strtok(NULL, " ");
    }

    int status;

    pid_t pid = fork(); // Alt süreç oluştur

    if (pid == -1) {
      perror("fork failed");
      exit(1);
    }

    if (pid == 0) { // Child process
      // execvp() ile komutu çalıştır
      if (execvp(args[0], args)) {
        perror("execvp failed");
        exit(1);
      }
    } else { // Parent process
      // Alt sürecin bitmesini bekle
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        exit(1);
      }

      // Alt sürecin çıkış durumu
      if (WIFEXITED(status)) {
        printf("Alt süreç başarıyla tamamlandı. Çıkış kodu: %d\n",
               WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Alt süreç bir sinyal nedeniyle sonlandı. Sinyal numarası: %d\n",
               WTERMSIG(status));
      }
    }
  }

  return 0;
}

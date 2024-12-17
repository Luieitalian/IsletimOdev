#include "redirect.h"

// Giriş yönlendirmesini işler (input redirection)
void handle_input_redirection(char *input_file) {
    int input_fd = open(input_file, O_RDONLY); // Giriş dosyasını okuma modunda açar
    if (input_fd == -1) {
        perror("Giriş dosyası bulunamadı");
        exit(1);
    }

    // Standart girdiyi giriş dosyasına yönlendirir
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2 giriş yönlendirme hatası");
        exit(1);
    }

    close(input_fd); // Giriş dosyasını kapatır
}

// Çıkış yönlendirmesini işler (output redirection)
void handle_output_redirection(char *output_file) {
    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Çıkış dosyasını yazma modunda açar
    if (output_fd == -1) {
        perror("Çıkış dosyası açılamadı");
        exit(1);
    }

    // Standart çıktıyı çıkış dosyasına yönlendirir
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2 çıkış yönlendirme hatası");
        exit(1);
    }

    close(output_fd); // Çıkış dosyasını kapatır
}

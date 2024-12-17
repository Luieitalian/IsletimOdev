#include "background.h"

// Arka plan komutunu çalıştıran fonksiyon
void run_background_process(char **args) {
    pid_t pid = fork();  // Yeni bir süreç oluşturur

    if (pid == 0) {  // Çocuk süreç
        // Çocuk süreçte komutu çalıştır
        if (execvp(args[0], args) == -1) {
            perror("execvp hatası");
        }
        exit(1);  // Çocuk süreç tamamlandığında sonlanır
    } else if (pid > 0) {  // Ebeveyn süreç
        // Ebeveyn süreç, çocuğun bitmesini beklemez
        printf("[%d] başlatıldı\n", pid);  // Arka plan işlem bilgisi
    } else {
        perror("fork hatası");
        exit(1);
    }
}

// Arka plan işlemlerinin bitmesini bekleyen fonksiyon
void wait_for_background_processes() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Çocuk süreçlerin bitmesini kontrol et
        if (WIFEXITED(status)) {
            printf("[%d] retval: %d\n", pid, WEXITSTATUS(status));  // Çıkış durumu bilgisi
        } else {
            printf("[%d] beklenmeyen bir durum oluştu\n", pid);
        }
    }
}

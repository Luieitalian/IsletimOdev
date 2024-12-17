#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"
#include "pipe.h"
#include "redirect.h"
#include "background.h"

// Kabuk prompt'unu yazdıran fonksiyon
void print_prompt() {
    printf("> ");
    fflush(stdout);  // Çıktı tamponunu boşalt
}

// Kabuk içindeki komutları işleyen ana fonksiyon
int main() {
    char *line = NULL;           // Kullanıcıdan alınacak komut satırı
    size_t len = 0;              // Komut satırının uzunluğu
    ssize_t nread;               // Okunan karakter sayısı
    char **args;                 // Komutun argümanları
    int background;              // Arka plan çalıştırma kontrolü

    // Arka plan işlemleri için sinyal işleyici
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;  // Arka plan işlemlerini yok say
    sigaction(SIGCHLD, &sa, NULL);

    while (1) {
        print_prompt();  // Komut istemini yazdır
        nread = getline(&line, &len, stdin);  // Kullanıcıdan komut al

        if (nread == -1) {  // EOF kontrolü (Ctrl+D ile çıkış)
            printf("\nÇıkılıyor...\n");
            break;
        }

        // Satırdaki sonlandırıcıyı kaldır
        line[strcspn(line, "\n")] = 0;

        // Eğer boş bir satırsa, yeni komut istemine geç
        if (strlen(line) == 0) {
            continue;
        }

        // Argümanları ayır
        args = parse_line(line);

        // Quit komutunu kontrol et
        if (strcmp(args[0], "quit") == 0) {
            // Arka planda çalışan süreçleri bekle
            wait_for_background_processes();
            break;
        }

        // Arka planda çalışacaksa, '&' kontrol et
        background = 0;
        if (args[nargs - 1] != NULL && strcmp(args[nargs - 1], "&") == 0) {
            background = 1;
            args[nargs - 1] = NULL;  // '&' karakterini argümanlardan kaldır
        }

        // Giriş yönlendirme varsa, işle
        if (has_input_redirection(args)) {
            handle_input_redirection(args);
        } 
        // Çıkış yönlendirme varsa, işle
        else if (has_output_redirection(args)) {
            handle_output_redirection(args);
        } 
        // Boru varsa, işle
        else if (has_pipe(args)) {
            handle_pipe(args);
        }
        // Arka planda işlem yoksa, standart bir komut çalıştır
        else if (background) {
            run_background_process(args);
        } else {
            run_single_command(args);
        }

        // Arka plan işlemlerinin bitmesini bekle
        wait_for_background_processes();
    }

    free(line);  // Bellek temizliği
    return 0;
}

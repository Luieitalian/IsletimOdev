#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Shell'in komutları çalıştırmak için kullanacağı fonksiyon prototipleri
void prompt(); // Komut istemini gösterir
void execute_command(char *command); // Komutu çalıştırır
void handle_builtin_commands(char **args); // Built-in komutları işler
int handle_input_redirection(char **args); // Giriş yönlendirmesi
int handle_output_redirection(char **args); // Çıkış yönlendirmesi
void execute_pipe_commands(char **args); // Borulama işlemi
void handle_background_process(char *command); // Arka plan komutlarını yönetir
void quit_shell(); // Kabuk sonlandırma komutu

// Yardımcı fonksiyonlar
void parse_command(char *input, char **args); // Komutu ve argümanları ayırır
int is_background_command(char *command); // Arka plan komutu olup olmadığını kontrol eder

#endif // SHELL_H

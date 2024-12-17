#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Giriş ve çıkış yönlendirme işlemlerini gerçekleştiren fonksiyonlar
void handle_input_redirection(char *input_file);  // Giriş yönlendirmesini işler
void handle_output_redirection(char *output_file); // Çıkış yönlendirmesini işler

#endif // REDIRECT_H

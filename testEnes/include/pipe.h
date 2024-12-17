#ifndef PIPE_H
#define PIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

// Boru işlemi için yardımcı fonksiyonlar
void handle_pipe(char *input); // Boru işlemini işler
void execute_pipe_commands(char **args, int num_pipes); // Birden fazla komut için boru işlemi
void close_pipes(int *pipefds, int num_pipes); // Boru dosya tanımlayıcılarını kapatır

#endif // PIPE_H

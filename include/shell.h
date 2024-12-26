#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_SIZE 100
#define MAX_ARG_COUNT 20
#define MAX_BG_PROCESSES 100

typedef struct {
    pid_t pid;
    int running;
} BackgroundProcess;

extern BackgroundProcess bg_processes[MAX_BG_PROCESSES];
extern int bg_process_count;

void yonlendirme_handle(char **args, int *arg_count);
void pipeline_calistir(char **args, int arg_count);
void komut_dizisi_calistir(char *input);
void cocukProses_bitis_handle(int sig);

//header dosyası - tüm tanımlamalar ve fonksiyon prototipleri
#endif 
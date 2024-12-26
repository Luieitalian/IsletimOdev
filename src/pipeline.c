#include "shell.h"

BackgroundProcess bg_processes[MAX_BG_PROCESSES];
int bg_process_count = 0;

void pipeline_calistir(char **args, int arg_count) {
    int background = 0;
    if (arg_count > 0 && strcmp(args[arg_count-1], "&") == 0) {
        background = 1;
        args[--arg_count] = NULL;
    }

    int pipe_positions[MAX_ARG_COUNT];
    int pipe_count = 0;
    
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_positions[pipe_count++] = i;
            args[i] = NULL;
        }
    }
}

void cocukProses_bitis_handle(int sig) {
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < bg_process_count; i++) {
            if (bg_processes[i].pid == pid && bg_processes[i].running) {
                printf("[%d] retval: %d\n", pid, WEXITSTATUS(status));
                bg_processes[i].running = 0;
                break;
            }
        }
    }
} 
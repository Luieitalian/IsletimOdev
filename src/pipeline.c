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
    
    // Pipe pozisyonu bul
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_positions[pipe_count++] = i;
            args[i] = NULL;
        }
    }

    // Eğer pipe yoksa, tek komutu çalıştır
    if (pipe_count == 0) {
        pid_t pid = fork();
        if (pid == 0) {
            yonlendirme_handle(args, &arg_count);
            execvp(args[0], args);
            perror("Komut çalıştırılamadı");
            exit(1);
        } else if (pid > 0) {
            if (background) {
                bg_processes[bg_process_count].pid = pid;
                bg_processes[bg_process_count].running = 1;
                bg_process_count++;
            } else {
                waitpid(pid, NULL, 0);
            }
        }
        return;
    }

    // Pipe ile çalıştırılan komutları işle
    int pipes[MAX_ARG_COUNT-1][2];
    for (int i = 0; i < pipe_count; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe oluşturulamadı");
            exit(1);
        }
    }

    int start = 0;
    pid_t last_pid;

    // Pipeline'daki her komutu çalıştır
    for (int i = 0; i <= pipe_count; i++) {
        int end = (i < pipe_count) ? pipe_positions[i] : arg_count;
        char **cmd = &args[start];
        cmd[end - start] = NULL;

        pid_t pid = fork();
        if (pid == 0) {
            // Çocuk işlem için pipe'ları ayarla
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            if (i < pipe_count) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Tüm pipe'ları kapat
            for (int j = 0; j < pipe_count; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            int cmd_arg_count = end - start;
            yonlendirme_handle(cmd, &cmd_arg_count);
            execvp(cmd[0], cmd);
            perror("Komut çalıştırılamadı");
            exit(1);
        }

        last_pid = pid;
        start = pipe_positions[i] + 1;
    }

    // Parent işlem için tüm pipe'ları kapat
    for (int i = 0; i < pipe_count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Arkaplan/ön planda çalıştırma işlemini işle
    if (background) {
        bg_processes[bg_process_count].pid = last_pid;
        bg_processes[bg_process_count].running = 1;
        bg_process_count++;
    } else {
        // Pipeline'daki tüm işlemleri bekle
        while (wait(NULL) > 0);
    }
}

void cocukProses_bitis_handle(int sig) {
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < bg_process_count; i++) {
            if (bg_processes[i].pid == pid && bg_processes[i].running) {
                printf("\n[%d] Proses bitti:  %d\n", pid, WEXITSTATUS(status));
                fflush(stdout);
                printf("> ");
                fflush(stdout);
                bg_processes[i].running = 0;
                break;
            }
        }
    }
} 
#include "shell.h"

void komut_dizisi_calistir(char *input) {
    char *command;
    char *saveptr1;
    
    command = strtok_r(input, ";", &saveptr1);
    while (command != NULL) {
        while (*command == ' ') command++;
        
        char *args[MAX_ARG_COUNT];
        int arg_count = 0;
        char *token;
        char *saveptr2;
        
        token = strtok_r(command, " ", &saveptr2);
        while (token != NULL && arg_count < MAX_ARG_COUNT - 1) {
            args[arg_count++] = token;
            token = strtok_r(NULL, " ", &saveptr2);
        }
        args[arg_count] = NULL;

        if (arg_count > 0) {
            pipeline_calistir(args, arg_count);
        }

        command = strtok_r(NULL, ";", &saveptr1);
    }
} 
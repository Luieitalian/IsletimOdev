#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Arka plan işlemlerini yöneten fonksiyonlar
void run_background_process(char **args);  // Arka plan komutunu başlatır
void wait_for_background_processes();      // Arka plan süreçlerinin bitmesini bekler

#endif // BACKGROUND_H

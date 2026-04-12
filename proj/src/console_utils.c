#include "../include/console_utils.h"
#include <stdio.h>
#ifdef _WIN32
    // Definir o valor manualmente (ATTACH_PARENT_PROCESS = -1)
    #define ATTACH_PARENT_PROCESS -1
    
    // Declarar funções do Windows
    __declspec(dllimport) int __stdcall AttachConsole(unsigned long dwProcessId);
    __declspec(dllimport) int __stdcall AllocConsole(void);
    __declspec(dllimport) int __stdcall FreeConsole(void);
#endif


void init_console(void)
{
    #ifdef _WIN32
        // ATTACH_PARENT_PROCESS é definido em windows.h
        if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
            printf("=== Debug Console ===\n");
            printf("CONSOLE OPEN WITH SUCCESS!\n");
        } else {
            // Se falhar, tenta apenas redirecionar
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
            printf("=== Debug Console (fallback) ===\n");
        }
    #endif
}

void close_console(void)
{
    #ifdef _WIN32
        printf("=== CLOSING ===\n");
        fflush(stdout);
        fflush(stderr);
        FreeConsole();
    #endif
}
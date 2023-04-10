#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024
int open_pipe (HANDLE* hPipe){
    *hPipe = CreateFile("\\\\.\\pipe\\pipeso",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if (*hPipe == INVALID_HANDLE_VALUE){
        printf("Falha em abrir o pipe. Codigo do erro: %d\n", GetLastError());
        return 1;
    }
    return 0;
}

int enviar_servidor(HANDLE* hPipe,char buffer[BUFFER_SIZE],  DWORD* dwWritten){
    if (!WriteFile(*hPipe, buffer, strlen(buffer) + 1, dwWritten, NULL)){// dwWritten é pasado por ponteiro, etão é pasado diretametne
        printf("Falha em escrever no pipe. Codigo do erro: %d\n", GetLastError());
        CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}
int receber_servidor(HANDLE* hPipe,char buffer[BUFFER_SIZE],  DWORD* dwRead){
    if (!ReadFile(*hPipe, buffer, BUFFER_SIZE, dwRead, NULL))// dwRead é pasado por ponteiro, etão é pasado diretametne
    {
        printf("Falha em ler do pipe. Codigo do erro: %d\n", GetLastError());
        CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}
int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead, dwWritten;

    open_pipe(&hPipe);
    printf("Conectado ao servidor!\n");
    printf("Entre com o dado a ser enviado: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    enviar_servidor(&hPipe, buffer,&dwWritten);
    printf("Dado enviado ao servidor.\n");
    receber_servidor(&hPipe, buffer, &dwRead);
    printf("Dado recebido: %s\n", buffer);
    CloseHandle(hPipe);
    
    return 0;
}
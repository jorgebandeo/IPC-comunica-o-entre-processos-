#include <stdio.h>
#include <windows.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
int open_pipe (HANDLE* hPipe, char nome[]){
    *hPipe = CreateFile(nome,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
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
    int confirmador = 1;
    HANDLE PipeDsplay;
    

    char bufferDsplay[BUFFER_SIZE];
    char bufferParada[BUFFER_SIZE];

    DWORD dwReadDsplay, dwWrittenDsplay;
    
    while (confirmador == 1){
        printf("0");
        confirmador = open_pipe(&PipeDsplay,"\\\\.\\pipe\\Dsplay");
    }
    confirmador = 1;
    
    
    printf("Conectado ao servidor!\n");
    while (confirmador == 1){
        printf("2.9");
        confirmador = receber_servidor(&PipeDsplay, bufferParada, &dwReadDsplay);
    }
    confirmador = 1;

    printf(bufferParada);
    sleep(5);
    while (bufferParada != "-1"){
        if(bufferParada == "1"){
            while (confirmador == 1){
                printf("1");
                confirmador = receber_servidor(&PipeDsplay, bufferDsplay, &dwReadDsplay);
            }
            confirmador = 1;
            
            printf(bufferDsplay);
        }
        

        if (receber_servidor(&PipeDsplay, bufferParada, &dwReadDsplay) == 1 ){
           sprintf(bufferDsplay,"0");
        }

        
    }
    printf("finaliza");
    CloseHandle(PipeDsplay);
    
    return 0;
}
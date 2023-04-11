#include <stdio.h>
#include <windows.h>

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
        //CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}
int receber_servidor(HANDLE* hPipe,char buffer[BUFFER_SIZE],  DWORD* dwRead){
    if (!ReadFile(*hPipe, buffer, BUFFER_SIZE, dwRead, NULL))// dwRead é pasado por ponteiro, etão é pasado diretametne
    {
        printf("Falha em ler do pipe. Codigo do erro: %d\n", GetLastError());
        //CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}
int main()
{
    int confirmador = 1;
    HANDLE PipeSensorA;

    char bufferSensorA[BUFFER_SIZE];
    char bufferParada[BUFFER_SIZE];

    DWORD dwReadSensorA, dwWrittenSensorA;
    while (confirmador == 1)
    {
        confirmador = open_pipe(&PipeSensorA,"\\\\.\\pipe\\SensorA");
    }
    confirmador = 1;
    sprintf(bufferParada, "%d", 0);
    
    
    
    int i =0;
    while (bufferParada != "-1"){
        if(bufferParada == "1"){
            printf("a.1");
            i = i +1;
            sprintf(bufferSensorA, "%d", i);
            printf("Dado recebido: %s\n", bufferSensorA);
            while (confirmador == 1){
                confirmador = enviar_servidor(&PipeSensorA, bufferSensorA,&dwWrittenSensorA);
            }
            confirmador = 1;
            printf("a.0");
        }
        printf("a.2");
        while (confirmador == 1){
            confirmador = receber_servidor(&PipeSensorA, bufferParada, &dwReadSensorA);
        }
        confirmador = 1;
    }
    
    CloseHandle(PipeSensorA);
    //CloseHandle(PipeParada);
    
    return 0;
}
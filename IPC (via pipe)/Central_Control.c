#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024
int crear_name_pipe(HANDLE* hPipe){// Create named pipe
    *hPipe = CreateNamedPipe("\\\\.\\pipe\\pipeso",PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,1,BUFFER_SIZE,BUFFER_SIZE,0,NULL);
    if (*hPipe == INVALID_HANDLE_VALUE){
        printf("Falha em criar o pipe. Codigo do erro: %d\n", GetLastError());
        return 1;
    }
 return 0;
}

int conectividade(HANDLE* hPipe){// Wait for client to connect
    
    if (!ConnectNamedPipe(*hPipe, NULL)){
        printf("Falha em conectar ao cliente. Codigo do erro: %d\n", GetLastError());
        CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}

int inizializador(HANDLE* hPipe){
    crear_name_pipe(hPipe);
    printf("Esperando o cliente conectar...\n");
    conectividade(hPipe);
}

int leitura_cliente(HANDLE* hPipe, char buffer[BUFFER_SIZE],DWORD* dwRead){// Read data from client
    if (!ReadFile(*hPipe, buffer, BUFFER_SIZE, dwRead, NULL)){//dwRead é pasado como ponteiro mas como a função ja recebe como ponteiro so é pasado seu endereço
        printf("Falha em ler do pipe. Codigo do erro: %d\n", GetLastError());
        CloseHandle(*hPipe);
        return 1;
    }
    return 0;
}

int escrita_cliente(HANDLE* hPipe, char buffer[BUFFER_SIZE],DWORD* dwRead){
    if (!WriteFile(*hPipe, buffer, *dwRead, NULL, NULL))
    {
        printf("Falha em escrever no pipe. Codigo do erro: %d\n", GetLastError());
        CloseHandle(*hPipe);
        return 1;
    }
}

int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead;
    inizializador(&hPipe);
    
    return 0;
}

    /*leitura_cliente(&hPipe, buffer, &dwRead);
    printf("Data recebido: %s\n", buffer);
    escrita_cliente(&hPipe, buffer, &dwRead);
    printf("Dado enviado de volta ao cliente.\n");
    CloseHandle(hPipe);*/
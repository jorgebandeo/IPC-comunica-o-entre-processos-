#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define BUFFER_SIZE 1024
int crear_name_pipe(HANDLE* hPipe, char nome[]){// Create named pipe
    *hPipe = CreateNamedPipe(nome,PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,1,BUFFER_SIZE,BUFFER_SIZE,0,NULL);
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

int inizializador(HANDLE* hPipe,char nome[]){
    int confirmador = 1;
    while (confirmador == 1)
    {
        confirmador = crear_name_pipe(hPipe, nome );
    }
    confirmador = 1;
    printf("Esperando o cliente conectar...\n");
    while (confirmador == 1)
    {
        confirmador = conectividade(hPipe);
    }
    confirmador = 1;
    
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
    return 0;
}
int sair(){
    int key;
    int time = 0;

    while (time < 100) {
        if (kbhit()) {
            key = getch();
            if (key == 27) {
                printf("Tecla ESC pressionada!\n");
                return 1;
            }
        }
        Sleep(10); // espera 0,1 segundos
        time += 10; // atualiza o tempo esperado
    }

    //printf("Nenhuma tecla pressionada!\n");
    return 0;
}
int main()
{

    int soma = 0;
    int soma_aniga = 0;
    int peso = 0;
    int confirmador = 1;

    char bufferParada[BUFFER_SIZE];

    

    HANDLE PipeSensorA;
    HANDLE PipeSensorB;
    HANDLE PipeDsplay;
    

    char bufferSensorA[BUFFER_SIZE];
    char bufferSensorB[BUFFER_SIZE];
    char bufferDsplay[BUFFER_SIZE];
    

    DWORD dwReadSensorA;
    DWORD dwReadSensorB;
    DWORD dwReadDsplay;
 
    
    //Inizialização dos resvidores que vao atender cada ususario
    inizializador(&PipeSensorA,"\\\\.\\pipe\\SensorA");
    inizializador(&PipeSensorB,"\\\\.\\pipe\\SensorB");
    inizializador(&PipeDsplay,"\\\\.\\pipe\\Dsplay");
    
    printf(" inicio");
    
    sprintf(bufferParada,"1");
    while (confirmador == 1){
        printf("0");
        confirmador = escrita_cliente(&PipeSensorA, bufferParada, &dwReadSensorA);
    }
    confirmador = 1; 
    while (confirmador == 1){//ERRO 
        printf("2");
        confirmador = escrita_cliente(&PipeDsplay, bufferParada, &dwReadDsplay);
    }
    confirmador = 1; 
    while (confirmador == 1){
        printf("1");
        confirmador = escrita_cliente(&PipeSensorB, bufferParada, &dwReadSensorB);
    }
    confirmador = 1; 
    
    printf("parada setada");

    while (sair() == 0)
    {   printf("processadno");
        while (confirmador == 1){
            confirmador = leitura_cliente(&PipeSensorA,bufferSensorA, &dwReadSensorA);
        }
        confirmador = 1;   
        while (confirmador == 1){
            confirmador = leitura_cliente(&PipeSensorB,bufferSensorB, &dwReadSensorB);
        }
        confirmador = 1;
        
        soma = atoi(bufferSensorA) + atoi(bufferSensorB);
        if (soma - soma_aniga >= 500){
            sprintf(bufferDsplay,"0");
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorA, bufferParada, &dwReadSensorA);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorB, bufferParada, &dwReadSensorB);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeDsplay, bufferParada, &dwReadDsplay);
            }
            confirmador = 1;

            peso = peso + atoi(bufferSensorA) * 2 + atoi(bufferSensorB)*5;
            soma_aniga = soma;
            
            
            sprintf(bufferDsplay,"1");
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorA, bufferParada, &dwReadSensorA);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorB, bufferParada, &dwReadSensorB);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeDsplay, bufferParada, &dwReadDsplay);
            }
            confirmador = 1;   
        }
        sprintf(bufferDsplay,"numero total de itens [%d] com um pesso calcuulado de [%s]",  soma, peso);
        while (confirmador == 1){
            confirmador = escrita_cliente(&PipeDsplay, bufferDsplay, &dwReadDsplay);
        }
        confirmador = 1;
        
    }
    sprintf(bufferParada,"-1");
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorA, bufferParada, &dwReadSensorA);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeSensorB, bufferParada, &dwReadSensorB);
            }
            confirmador = 1;
            while (confirmador == 1){
                confirmador = escrita_cliente(&PipeDsplay, bufferParada, &dwReadDsplay);
            }
            confirmador = 1;
     
    CloseHandle(PipeSensorA);
    CloseHandle(PipeSensorB);
    CloseHandle(PipeDsplay);
    
    return 0;
}


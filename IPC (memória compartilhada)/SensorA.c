/*
Produtor - Testado no CLion https://learn.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory
*/
#include <windows.h>

#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <string.h>
#pragma comment(lib, "user32.lib")
#define BUF_SIZE 256


int Memoria_open(TCHAR szName[], HANDLE* hMapFile, LPCTSTR* pBuf){
    
    *hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);

    if (*hMapFile == NULL){
        _tprintf(TEXT("Could not open file mapping object (%d).\n"),GetLastError());
        return 0;
    }

    *pBuf = (LPTSTR) MapViewOfFile(*hMapFile,FILE_MAP_ALL_ACCESS,0,0,BUF_SIZE);

    if (*pBuf == NULL){
        _tprintf(TEXT("Could not map view of file (%d).\n"),GetLastError());
        CloseHandle(*hMapFile);
        return 0;
    }
    
    return 1;
}
int Memoria_create(TCHAR szName[], HANDLE* phMapFile, LPCTSTR* ppBuf) {
    *phMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, szName); 

    if (*phMapFile == NULL) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
        return 0;
    }

    *ppBuf = (LPTSTR) MapViewOfFile(*phMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);

    if (*ppBuf == NULL) {
        _tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
        CloseHandle(*phMapFile);
        return 0;
    }

    return 1;
}
int _tmain()
{
    boolean T = TRUE;
    int Verificador = 0;

    // Criados
    TCHAR Sensor_memore[] = TEXT("SensorA");
    HANDLE hMapFile;
    LPCTSTR Sensor;

    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_create(Sensor_memore, &hMapFile, &Sensor);
    }
    Verificador = 0;
    printf("a");
    TCHAR szNamePausa[]=TEXT("Pausa");
    TCHAR szNameLigar[]=TEXT("Ligar");
    HANDLE hMapFilePausa;
    HANDLE hMapFileLigar;
    LPCTSTR pBufPausa;
    LPCTSTR pBufLigar;
    
    // Abertos
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNamePausa, &hMapFilePausa, &pBufPausa);
    }
    printf("B");
    Verificador = 0;
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameLigar, &hMapFileLigar, &pBufLigar);
    }
    Verificador = 0;
    printf("aaa");
    
    while (atoi(pBufLigar) == 1)
    {
        printf(pBufPausa);
            if(atoi(pBufPausa) == 0){
                printf("e");
                TCHAR novo[10];
                wsprintf(novo, TEXT("%d"), 0);
                CopyMemory((PVOID)Sensor, novo, (_tcslen(novo) + 1) * sizeof(TCHAR));

                printf("Pressione qualquer letra para continuar...");
                getchar(); // Aguarda pela ação de qualquer letra
                printf("\nContinuando a execução do programa...");
            
                for (size_t i = 0; i >=0 ; i++){
                    Sleep(1000);
                    TCHAR novo[10];
                    wsprintf(novo, TEXT("%d"), i);
                    printf(novo);
                    printf("\n");
                    CopyMemory((PVOID)Sensor, novo, (_tcslen(novo) + 1) * sizeof(TCHAR));
                }
            }
       
            
       
    }
    
            UnmapViewOfFile(pBufPausa);
            UnmapViewOfFile(pBufLigar);
            UnmapViewOfFile(Sensor);
            CloseHandle(hMapFilePausa);
            CloseHandle(hMapFileLigar);
            CloseHandle(hMapFile);

            return 0;
}

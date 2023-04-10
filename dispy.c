/*
Consumidor - Testado no CLion https://learn.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory
*/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#pragma comment(lib, "user32.lib")
#define BUF_SIZE 256
LPCTSTR Tru = TEXT("True");
LPCTSTR Fal = TEXT("False");
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
    //Criados 
    // Abertos]
    TCHAR szNameLigar[]=TEXT("Ligar");
    TCHAR szNamePeso[]=TEXT("Peso");
    TCHAR szNameA[]=TEXT("SensorA");
    TCHAR szNameB[]=TEXT("SensorB");
    HANDLE hMapFileLigar;
    HANDLE hMapFilePeso;
    HANDLE hMapFileA;
    HANDLE hMapFileB;
    LPCTSTR pBufLigar;
    LPCTSTR pBufPeso;
    LPCTSTR pBufA;
    LPCTSTR pBufB;
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameLigar, &hMapFileLigar, &pBufLigar);
    }
    Verificador = 0;
    printf("%s",pBufLigar);
    getchar();
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNamePeso, &hMapFilePeso, &pBufPeso);
    }
    Verificador = 0;
    printf("b");
    while (Verificador == 0){
        Verificador = Memoria_open(szNameA, &hMapFileA, &pBufA);
    }
    Verificador = 0;
    printf("c");
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameB, &hMapFileB, &pBufB);
    }
    while (atoi(pBufLigar) == 1){   

        system("cls");
        int soma = atoi(pBufA) + atoi(pBufB);
        printf("numero total de itens [%d] com um pesso calcuulado de [%s]",  soma, pBufPeso);
        Sleep(2000);
    }
    
            UnmapViewOfFile(pBufLigar);
            UnmapViewOfFile(pBufPeso);
            UnmapViewOfFile(pBufLigar);
            UnmapViewOfFile(pBufA);
            UnmapViewOfFile(pBufB);
            CloseHandle(hMapFileLigar);
            CloseHandle(hMapFilePeso);
            CloseHandle(hMapFileLigar);
            CloseHandle(hMapFileA);
            CloseHandle(hMapFileB);

            return 0;

    
}

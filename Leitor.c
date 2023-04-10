/*
Consumidor - Testado no CLion https://learn.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory
*/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#pragma comment(lib, "user32.lib")
#define BUF_SIZE 256
LPTSTR Tru = TEXT("True");
LPTSTR Fal = TEXT("False");
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
    int peso = 0;
    int Verificador = 0;
    //Criados 
    TCHAR szNamePausa[]=TEXT("Pausa");
    TCHAR szNamePeso[]=TEXT("Peso");
    TCHAR szNamesom[]=TEXT("som");
    HANDLE hMapFilePausa;
    HANDLE hMapFilesom;
    HANDLE hMapFilePeso;
    LPCTSTR pBufPausa;
    LPCTSTR pBufsom;
    LPCTSTR pBufPeso;
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_create(szNamesom, &hMapFilesom, &pBufsom);
    }
    Verificador = 0;
    TCHAR n1[10];
    wsprintf(n1, TEXT("%d"), 0);
    CopyMemory((PVOID)pBufsom, n1, (_tcslen(n1) + 1) * sizeof(TCHAR));
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_create(szNamePausa, &hMapFilePausa, &pBufPausa);
    }
    Verificador = 0;
    CopyMemory((PVOID)pBufPausa, TEXT("0"), (_tcslen(TEXT("0"))) * sizeof(TCHAR));
    printf("a");

    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_create(szNamePeso, &hMapFilePeso, &pBufPeso);
    }
    Verificador = 0;
    
    // Abertos
    TCHAR szNameLigar[]=TEXT("Ligar");
    TCHAR szNameA[]=TEXT("SensorA");
    TCHAR szNameB[]=TEXT("SensorB");
    HANDLE hMapFileLigar;
    HANDLE hMapFileA;
    HANDLE hMapFileB;
    LPCTSTR pBufLigar;
    LPCTSTR pBufA;
    LPCTSTR pBufB;

    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameLigar, &hMapFileLigar, &pBufLigar);
    }
    Verificador = 0;
    printf("c");
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameA, &hMapFileA, &pBufA);
    }
    Verificador = 0;
    printf("d");
    while (Verificador == 0){
        system("cls");
        Verificador = Memoria_open(szNameB, &hMapFileB, &pBufB);
    }
    Verificador = 0;
    printf("e");
    TCHAR X[10];
    wsprintf(X, TEXT("%d"), 0);
    CopyMemory((PVOID)pBufPeso, X, (_tcslen(X) + 1) * sizeof(TCHAR));
    printf("b");
    printf("%d", atoi(pBufLigar));
    while (atoi(pBufLigar) == 1){
            Sleep(2000);
            int soma = atoi(pBufA) + atoi(pBufB);
            printf("%s + %s = %d", pBufA, pBufB, soma);
            printf("\n");
            if (soma-atoi(pBufsom)>=500){
                CopyMemory((PVOID)pBufPausa, TEXT("1"), (_tcslen(TEXT("1"))) * sizeof(TCHAR));
                peso = peso + (atoi(pBufA) * 2) + (atoi(pBufB) * 5);
                TCHAR novo[1000];
                TCHAR n2[10];
                wsprintf(n2, TEXT("%d"), soma+atoi(pBufsom));
                CopyMemory((PVOID)pBufsom, n2, (_tcslen(n2) + 1) * sizeof(TCHAR));


                wsprintf(novo, TEXT("%d"), peso);
                CopyMemory((PVOID)pBufPeso, novo, (_tcslen(novo) + 1) * sizeof(TCHAR));
                CopyMemory((PVOID)pBufPausa, TEXT("0"), (_tcslen(TEXT("0"))) * sizeof(TCHAR));
            }
        
    }
            UnmapViewOfFile(pBufPausa);
            UnmapViewOfFile(pBufsom);
            UnmapViewOfFile(pBufPeso);
            UnmapViewOfFile(pBufLigar);
            UnmapViewOfFile(pBufA);
            UnmapViewOfFile(pBufB);
            CloseHandle(hMapFilesom);
            CloseHandle(hMapFilePausa);
            CloseHandle(hMapFilePeso);
            CloseHandle(hMapFileLigar);
            CloseHandle(hMapFileA);
            CloseHandle(hMapFileB);

            return 0;
    
}

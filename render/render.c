#define UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

#pragma comment(lib, "User32.lib")

void kbdListen(void);
void ClearScreen(void);
void WriteTitle(int ThreadNum);
HANDLE kbdThread;
HANDLE hRunMutex;
COORD ConsoleSize;
HANDLE hConsoleOut;
HANDLE hScreenMutex;
BOOL running = TRUE;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

int main(void)
{
    // Get display screen information and clear the screen.
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    ConsoleSize.X = csbiInfo.srWindow.Right;
    ConsoleSize.Y = csbiInfo.srWindow.Bottom;
    ClearScreen();
    SetConsoleTitleW("Olá, mundo!");

    // Create Screen mutex
    hScreenMutex = CreateMutexW(NULL, FALSE, NULL);
    hRunMutex = CreateMutexW(NULL, TRUE, NULL);
    
    // Add keys listener
    KbdListen();

    // All threads done, clean up Handles
    if(hScreenMutex) CloseHandle(hScreenMutex);
    if(hConsoleOut) CloseHandle(hConsoleOut);
    if(hRunMutex) CloseHandle(hRunMutex);
}

void ClearScreen(void)
{
    COORD home = {0, 0};
    FillConsoleOutputCharacterW(hConsoleOut, L' ', ConsoleSize.X * ConsoleSize.Y, home, NULL);
}

void shutdown(void)
{
    ReleaseMutex(hRunMutex);

    WaitForSingleObject(Threads, INFINITE)
}

/*
void kbdListen(void)
{
    while(running)
    {
        if(getAsyncKeyState('W'))
        {

        }
        else if(getAsyncKeyState('A'))
        {

        }
        else if(getAsyncKeyState('S'))
        {

        }
        else if(getAsyncKeyState('D'))
        {

        }
    }
}
*/
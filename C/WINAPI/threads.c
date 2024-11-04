#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define MAX_THREADS 32

// The function returns a random number between min and max, which must be in integer range
#define getrandom(min, max) (SHORT)((rand() % (int)(((max) + 1) - (min))) + (min)) 


int main(void);
void KbdFunc(void);
void BounceProc(void* pMyID);
void ClearScreen(void);
void ShutDown(void);
void WriteTitle(int ThreadNum);

HANDLE hConsoleOut;
HANDLE hRunMutex;
HANDLE hScreenMutex;
int ThreadNr = 0;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
COORD consoleSize;
BOOL bTrails = FALSE;

HANDLE hThreads[MAX_THREADS] = {NULL};

int main(void)
{
    // Get display screen information and clear the screen.
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    consoleSize.X = csbiInfo.srWindow.Right;
    consoleSize.Y = csbiInfo.srWindow.Bottom;
    ClearScreen();
    WriteTitle(0);

    // Create screen mutex and reset thread count.
    hScreenMutex =  CreateMutexW(NULL, FALSE, NULL);
    hRunMutex = CreateMutexW(NULL, TRUE, NULL);

    // Starts waiting for keyboard input to dispatch threads or exit.
    KbdFunc();

    // All threads done. Clean up handles.
    if(hScreenMutex) CloseHandle(hScreenMutex);
    if(hRunMutex) CloseHandle(hRunMutex);
    if(hConsoleOut) CloseHandle(hConsoleOut);
}

void ShutDown(void)
{
    // Tell all threads to die.
    ReleaseMutex(hRunMutex);

    while(ThreadNr > 0)
    {
        WaitForSingleObject(hThreads[--ThreadNr], INFINITE);
    }

    // Clean up display when done.
    WaitForSingleObject(hScreenMutex, INFINITE);
    ClearScreen();
}

void KbdFunc(void)
{
    int KeyInfo;
    do
    {
        KeyInfo =_getch();
        if(tolower(KeyInfo) == 'a' && ThreadNr < MAX_THREADS)
        {
            ++ThreadNr;
            hThreads[ThreadNr] = (HANDLE)_beginthread(BounceProc, 0, (void*)(uintptr_t)ThreadNr);
            WriteTitle(ThreadNr);
        }

        if(tolower(KeyInfo) == 't')
        {
            bTrails = !bTrails;
        }
    } while(tolower(KeyInfo) != 'q');

    ShutDown();
}

void BounceProc(void* pMyID)
{
    wchar_t MyCell, OldCell;
    WORD MyAttrib, OldAttrib = 0;
    wchar_t BlankCell = 0x20;
    COORD Coords, Delta;
    COORD Old = {0, 0};
    DWORD Dummy;
    int MyID = (int)(uintptr_t)pMyID;

    // Generate upcoming increments and initial display coordinates.
    Coords.X = getrandom(0, consoleSize.X - 1);
    Coords.Y = getrandom(0, consoleSize.Y - 1);
    Delta.X = getrandom(-3, 3);
    Delta.Y = getrandom(-3, 3);

    // Set up characteres & generate color atribute from threads number.
    if(MyID > 16)
        MyCell = (wchar_t)(0x60 + MyID - 16); // Lower case.
    else
        MyCell = (wchar_t)(0x40 + MyID); // Upper case.
    MyAttrib = MyID & 0x0f; // Force black background.

    do
    {
        // Wait for display to be avaliable, then lock it
        WaitForSingleObject(hScreenMutex, INFINITE);

        if(bTrails)
        {
            ReadConsoleOutputCharacterW(hConsoleOut, &OldCell, 1, Old, &Dummy);
            ReadConsoleOutputCharacterW(hConsoleOut, &OldAttrib, 1, Old, &Dummy);
            if((OldCell == MyCell) && (OldAttrib == MyAttrib))
                WriteConsoleOutputCharacterW(hConsoleOut, &BlankCell, 1, Old, &Dummy);
        }

        WriteConsoleOutputCharacterW(hConsoleOut, &MyCell, 1, Coords, &Dummy);
        WriteConsoleOutputAttribute(hConsoleOut, &MyAttrib, 1, Coords, &Dummy);
        ReleaseMutex(hScreenMutex);

        // Increment the coordinates for the next placement of the block.
        Old.X = Coords.X;
        Old.Y = Coords.Y;
        Coords.X += Delta.X;
        Coords.Y += Delta.Y;

        // If we are about to go off the screen, reverse the direction.
        if(Coords.X < 0 || Coords.X >= consoleSize.X)
        {
            Delta.X = -Delta.X;
            Beep(400, 50);
        }
        if(Coords.Y < 0 || Coords.Y >= consoleSize.Y)
        {
            Delta.Y = -Delta.Y;
            Beep(600, 50);
        }
    }
    // Repeat while RunMutex is still broken
    while (WaitForSingleObject(hRunMutex, 75L) == WAIT_TIMEOUT);
}

void WriteTitle(int ThreadNum)
{
    enum
    {
        sizeOfNThreadMsg = 120
    };
    wchar_t NThreadMsg[sizeOfNThreadMsg] = {L""};

    swprintf_s(NThreadMsg, sizeOfNThreadMsg, L"Threads running: %02d. Press 'A' to start a thread, 'T' to toggle trails, 'Q' to quit.", ThreadNum);
    SetConsoleTitleW(NThreadMsg);
}

void ClearScreen(void)
{
    DWORD dummy = 0;
    COORD Home = {0, 0};
    FillConsoleOutputCharacterW(hConsoleOut, L' ', consoleSize.X * consoleSize.Y, Home, &dummy);
}
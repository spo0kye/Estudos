// Somehow slow compared to the C# version
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <process.h>
#define LCtrl_KeyCode 162
#pragma comment(lib, "User32.lib")


void click(void);
void VerifyPos(void);
void verifyKey(void);
BOOL running = 1;
BOOL state = FALSE;
BOOL keyPressed = FALSE;
POINT coords;
HANDLE hThreadClick;
HANDLE hThreadGetPos;


int main(void)
{
    hThreadClick = (HANDLE)_beginthread((void *)click, 0, NULL);
    while (TRUE)
    {
        Sleep(100);
        if ((GetAsyncKeyState('A') & 0x8000) > 0)
        {
            if (!keyPressed)
            {
                state = !state;
                keyPressed = TRUE;
            }
        }

       else if ((GetAsyncKeyState('s') & 0x8000) > 0)
        {
            CloseHandle(hThreadClick);
            return;
        }

        else
            keyPressed = FALSE;
    }
}


void click(void)
{
    while (TRUE)
    {
        while (state)
        {
            // Can crash entire system when running on low-end PCs
            Sleep(10);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }
}
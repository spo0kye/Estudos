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
HANDLE hThreadGetKey;

int main(void)
{
    hThreadClick = (HANDLE)_beginthread((void *)click, 0, NULL);
    hThreadGetPos = (HANDLE)_beginthread((void *)VerifyPos, 0, NULL);
    hThreadGetKey = (HANDLE)_beginthread((void *)verifyKey, 0, NULL);
    while (running)
    {
    }
}

void click(void)
{
    while (TRUE)
    {
        while (state)
        {
            // Can crash entire system when running on low-end PCs
            Sleep(1);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, coords.x, coords.y, 0, 0);
        }
    }
}

void VerifyPos(void)
{
    while (state)
    {
        GetCursorPos(&coords);
    }
}

void verifyKey(void)
{
    while (1)
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
        else if ((GetAsyncKeyState(LCtrl_KeyCode) & 0x8000) > 0)
        {
            CloseHandle(hThreadClick);
            CloseHandle(hThreadGetPos);
            CloseHandle(hThreadGetKey);
            running = FALSE;
            return;
        }
        else
            keyPressed = FALSE;
    }
}
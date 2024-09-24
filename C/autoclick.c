// Somehow inneficient compared to the C# version

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
HANDLE hThreadVerPos;
HANDLE hThreadVerKey;

int main(void)
{
    hThreadClick = (HANDLE)_beginthread(click, 0, NULL);
    hThreadVerPos = (HANDLE)_beginthread(VerifyPos, 0, NULL);
    hThreadVerKey = (HANDLE)_beginthread(verifyKey, 0, NULL);
    while(running){}
}

void click(void)
{
    while(TRUE)
    {
        while(state)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, coords.x, coords.y, 0, 0);
        }
    }
}

void VerifyPos(void)
{
    while(state)
    {
        GetCursorPos(&coords);
    }
}

void verifyKey(void)
{
    while(1)
        {
            Sleep(100);
            if((GetAsyncKeyState('A') & 0x8000) > 0)
            {
                if(!keyPressed)
                {   
                    state = !state;
                    keyPressed = TRUE;
                }
            }
            else if((GetAsyncKeyState(0x53) & 0x8000) > 0)
            {
                CloseHandle(hThreadClick);
                CloseHandle(hThreadVerPos);
                CloseHandle(hThreadVerKey);
                running = FALSE;
                return;
            }
            else
                keyPressed = FALSE;
        }
}
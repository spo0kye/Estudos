// need to be compiled with -municode in gcc or /utf-8 in CL
#include <windows.h>
#pragma comment(lib, "User32.lib")

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPWSTR cmdline, int cmdshow)
{
    MessageBoxW(NULL, L"Olá, mundo!", cmdline, MB_OK);
    return 0;
}
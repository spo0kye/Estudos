 /* Need to be compiled with -municode */

#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPWSTR cmdline, int cmdshow) {

    MessageBoxW(NULL, (LPCWSTR)cmdline , L"Olá, mundo", MB_OK);

    return 0;
}
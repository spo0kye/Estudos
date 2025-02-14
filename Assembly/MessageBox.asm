; ld.exe {filename} -L{folder to lib, Ex: -LC:\Windows\System32\} {-l + lib for every aditional lib} -o {output filename with extension}
; NASM win64
bits 64

NULL EQU 0
STD_OUT_HANDLE EQU -11

extern ExitProcess
extern MessageBoxA

global inicio

section .data
    message db "Hello, World!", 0
    title db "Hello, Enzo!", 0

section .text

inicio:
    ; Prepare arguments for MessageBoxA
    ; __FASTCALL standard
    xor rcx, rcx      ; Parent window (Hwnd) = NULL
    mov rdx, title    ; Title address to rdx
    mov r8, message  ; Message address to r8
    mov r9, 0         ; MB_OK box type

    sub rsp, 8        ; idk why it won't work without it
    call MessageBoxA

    ; ExitProcess call
    push 0
    xor ecx, ecx      ; uExitCode = 0
    call ExitProcess
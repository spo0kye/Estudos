using System.Runtime.InteropServices;
using System.Threading;
using System;
using System.Drawing;
using System.Security.Cryptography;

namespace autoclick;

class Program
{
    public struct MOUSEINPUT
    {
        public int dx;
        public int dy;
        public uint mouseData;
        public uint dwFlags;
        public uint time;
        // It should be a pointer but i'm not using it so i just make it NULL.
        public UIntPtr dwExtraInfo;
    }

    // I will not put definitions for the KEYBOARDINPUT and HARDWAREINPUT cuz i'm not using it.
    [StructLayout(LayoutKind.Sequential)]
    public struct INPUT
    {
        public Int32 type;
        public MOUSEINPUT MI;
    }

    [DllImport("user32.dll")]
    private static extern short GetAsyncKeyState(int vKey);
    [DllImport("user32.dll")]
    private static extern void mouse_event(int dwFlag, int dx, int dy, int dwData, ulong dxExtraInfo);
    [DllImport("user32.dll")]
    private static extern bool GetCursorPos(out Point lpPoint);
    [DllImport("user32.dll")]
    private static extern uint SendInput(uint nInput, INPUT[] pInputs, int cbSize);
    public static bool state = false;
    public static bool pressed = false;
    const int MOUSEEVENTF_LEFTDOWN = 0x0002;
    const int MOUSEEVENTF_LEFTUP = 0x0004;

    public static void Main(String[] args)
    {
        Thread clicker = new Thread(MouseEventVer);
        clicker.Start();

        Console.WriteLine(typeof(Point));
        Console.WriteLine("Running...");
        while (true)
        {
            const int key = 162; //Left Ctrl key code
            Thread.Sleep(50);    // Laggy without it
            if ((GetAsyncKeyState(key) & 0x8000) > 0)
            {
                if (!pressed)
                {
                    state = !state;
                    pressed = true;
                }
            }
            else
                pressed = false;
        }
    }

    private static void MouseEventVer()
    {
        while (true)
            if (state)
            {
                Thread.Sleep(10);
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
    }

    private static void SendInputVer()
    {
        // 0 for the MOUSE_INPUT
        INPUT InputDown = new INPUT
        {
            type = 0,
            MI = new MOUSEINPUT
            {
                dwFlags = MOUSEEVENTF_LEFTDOWN,
            }
        };
        INPUT InputUp = InputDown;
        InputUp.MI.dwFlags = MOUSEEVENTF_LEFTUP;
        uint error = 0;
        while (true)
        {
            if (state)
            {
                Thread.Sleep(1); // Can lag a lot without it
                error = SendInput(1, new INPUT[] { InputDown }, Marshal.SizeOf(typeof(INPUT)));
                _ = SendInput(1, new INPUT[] { InputUp }, Marshal.SizeOf(typeof(INPUT)));
            }
        }
    }
}
using System.Runtime.InteropServices;
using System.Threading;
using System;
using System.Drawing;
using System.Security.Cryptography;

namespace autoclick;

static class Program
{
    [DllImport("user32.dll")]
    private static extern short GetAsyncKeyState(int vKey);
    [DllImport("user32.dll")]
    private static extern void mouse_event(int dwFlag, int dx, int dy, int dwData, ulong dxExtraInfo);
    [DllImport("user32.dll")]
    private static extern bool GetCursorPos(out Point lpPoint);

    public static void Main(String[] args)
    {
        bool state = false;
        bool pressed = false;
        Thread clicker = new Thread(() =>
        {
            while (true)
                if (state)
                {
                    Thread.Sleep(10);
                    GetCursorPos(out Point Pos);
                    const int MOUSEEVENTF_LEFTDOWN = 0x0002;
                    const int MOUSEEVENTF_LEFTUP = 0x0004;
                    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, Pos.X, Pos.Y, 0, 0);
                }
        });
        clicker.Start();

        Console.WriteLine("Running...");
        while (true)
        {
            const int key = 162;
            Thread.Sleep(5);
            if ((GetAsyncKeyState(key) & 0x8000) > 0)
                if (!pressed)
                {
                    state = !state;
                    pressed = true;
                }
            pressed = false;
        }
    }
}
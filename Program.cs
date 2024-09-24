using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace autoclick;

public class Program
{
    [DllImport("User32.dll")]
    public static extern short GetAsyncKeyState(Keys ArrowKeys);
    [DllImport ("User32.DLL")]
    private static extern bool GetCursorPos(out CursorPos lpPoint);
    [DllImport ("User32.DLL")]
    public static extern void mouse_event(long dwFlags, long dx, long dy, long cButtons, long dwExtraInfo);
    public struct CursorPos { public long X; public long Y; }
    const int MOUSEEVENTF_LEFTDOWN = 0x02;
    const int MOUSEEVENTF_LEFTUP = 0x04;
    private static bool state = false;

    private static void click()
    {
        while(true)
        {
            while(state)
            {
                //Thread.Sleep(10);
                GetCursorPos(out CursorPos position);
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, position.X, position.Y, 0, 0);
            }
        }
    }
    
        public static void Main(String[] Args)
    {
        Thread clicker = new Thread(click);
        clicker.Start();
    
        bool keyOn;
        bool keyAlreadyPressed = false;
        while(true)
        {
            Thread.Sleep(30);
            keyOn = (GetAsyncKeyState(Keys.LControlKey) & 0x8000) > 0; // Compare the most significant bit of a short
            if(keyOn)
            {
                if(!keyAlreadyPressed)
                {
                    state = !state;
                    keyAlreadyPressed = true;
                }
            }

            else
                keyAlreadyPressed = false;
        }
    }
}
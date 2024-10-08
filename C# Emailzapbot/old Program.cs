using OL = Microsoft.Office.Interop.Outlook;
using Microsoft.Toolkit.Uwp.Notifications;
using System.Runtime.InteropServices;
using Windows.Media.Capture.Core;
using System.Drawing.Imaging;


namespace emailzapcs;


class Program
{
    [DllImport("User32.dll")]
    public static extern short GetAsyncKeyState();

    [DllImport("gdi32.dll")]
    public static extern bool DeleteObject(IntPtr hObject);

    [DllImport("System.Runtime.dll")]
    public static extern string GetTempPath();
    public static readonly string TempPath = Path.GetTempPath();
    public static readonly ImageFormat formato = ImageFormat.Png;
    public static Thread ShowThread = new Thread(() => EmailCreate(TempPath + "\\PrtScrnImg." + formato.ToString()));
    
    public static bool send = false;
    static void Main(string[] args)
    {
        Thread thread = new Thread(() => CatchImage());
        thread.SetApartmentState(ApartmentState.STA);
        thread.Start();
        ToastNotificationManagerCompat.OnActivated += toastArgs =>
        {
            ShowThread.Start();
            send = false;
        };
    }

    private static void EmailCreate(string file)
    {
        OL.Application outlookApp = new OL.Application();
        OL.MailItem mailItem = (OL.MailItem)outlookApp.CreateItem(OL.OlItemType.olMailItem);
        mailItem.To = "enzo.szk@gmail.com";
        mailItem.Subject = "Hello world! subject";
        mailItem.Body = "This is the body";
        mailItem.Attachments.Add(file);
        mailItem.Display(true);
        File.Delete(TempPath + "\\PrtScrnImg." + formato.ToString());
        return;
    }

    public static void CatchImage()
    {
        while(true)
        {
            Thread.Sleep(200);
            Console.WriteLine(send);
            if(Clipboard.ContainsImage() && !send)
            {
                Clipboard.GetImage().Save(TempPath + "\\PrtScrnImg." + formato.ToString(), formato);
                new ToastContentBuilder().AddText("Olá, mundo!").Show();
                send = true;
                Clipboard.Clear();
            };
        }
    }
}
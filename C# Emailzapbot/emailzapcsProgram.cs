//dotnet publish --output {path} --runtime win10-x64 --configuration Release -p:PublishSingleFile=true -p:PublishTrimmed=false --self-contained

using OL = Microsoft.Office.Interop.Outlook;
using Microsoft.Toolkit.Uwp.Notifications;
using System.Runtime.InteropServices;
using Windows.Media.Capture.Core;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System;


namespace emailzapcs;


class Program
{
    [DllImport("System.Runtime.dll")]
    public static extern string GetTempPath();
    public static readonly string TempPath = Path.GetTempPath();
    public static readonly ImageFormat formato = ImageFormat.Png;
    public static bool send = false;
    private static ContextMenuStrip trayMenu;
    private static NotifyIcon notifyIcon;
    public static void Main(string[] args)
    {
        Thread notifyThread = new Thread(delegate(){
            trayMenu = new ContextMenuStrip();
            trayMenu.Items.Add("Sair", null, OnExit);

            notifyIcon = new NotifyIcon();
            notifyIcon.Text = "ScreenShot listener";
            notifyIcon.Icon = new Icon(SystemIcons.Application, 40, 40);
            notifyIcon.ContextMenuStrip = trayMenu;
            notifyIcon.Visible = true;

            notifyIcon.MouseClick += TrayiconMouseClick;
            Application.Run();
        });
        notifyThread.Start();

        string path = Directory.GetCurrentDirectory().ToString();
        Thread thread = new Thread(() => CatchImage());
        thread.SetApartmentState(ApartmentState.STA);
        thread.Start();
        ToastNotificationManagerCompat.OnActivated += toastArgs =>
        {
            Process.Start(path + "\\OLOpen.exe");
            send = false;
        };
    }

    public static void CatchImage()
    {
        while(true)
        {
            Thread.Sleep(100);
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

    private static void OnExit(object sender, EventArgs e)
    {
        // Limpa o ícone da bandeja e encerra a aplicação
        notifyIcon.Dispose();
        Environment.Exit(0);
        Application.Exit();
    }

    private static void TrayiconMouseClick(object sender, MouseEventArgs e)
    {
        if(e.Button == MouseButtons.Left || e.Button == MouseButtons.Right)
        {
            trayMenu.Show(Cursor.Position);
        }
    }
}

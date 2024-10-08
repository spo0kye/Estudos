using OL = Microsoft.Office.Interop.Outlook;
using Windows.Media.Capture.Core;
using System.Drawing.Imaging;
using System;

namespace OLOpen;
class Program
{
    public static readonly string TempPath = Path.GetTempPath();
    public static readonly ImageFormat formato = ImageFormat.Png;
    public static void Main(string[] args)
    {
        OL.Application outlookApp = new OL.Application();
        OL.MailItem mailItem = (OL.MailItem)outlookApp.CreateItem(OL.OlItemType.olMailItem);
        mailItem.To = "enzo.szk@gmail.com";
        mailItem.Subject = "Hello world! subject";
        mailItem.Body = "This is the body";
        mailItem.Attachments.Add(TempPath + "\\PrtScrnImg." + formato.ToString());
        mailItem.Display(true);
        File.Delete(TempPath + "\\PrtScrnImg." + formato.ToString());
        return;
    }
}
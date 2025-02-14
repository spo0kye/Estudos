using System;
using System.Net;
using System.Text;
using System.Net.Sockets;
using System.Net.Cache;

namespace Server;

class Program
{
    public static void Main(string[] args)
    {
        using var listener = new HttpListener();
        listener.Prefixes.Add("http://localhost:3389/");
        listener.Start();
        Console.WriteLine("Listening on port 3389");

        while(true)
        {
            HttpListenerContext ctx = listener.GetContext();
            using HttpListenerResponse resp = ctx.Response;

            HttpListenerRequest req = ctx.Request;
            Console.WriteLine("OK");

            if(ctx.Request.Url?.LocalPath == "/shutdown")
            {
                Console.WriteLine("Remote shutdown activated");
                return;
            }

            else if(ctx.Request.Url?.LocalPath == "/img")
                if(!SendImage(ctx, @"C:\teste\imag.png"))
                    NotFound(ctx);
            
            else if(ctx.Request.Url?.LocalPath == "/")
                SendHTML(ctx, @"C:\teste\index.html");

            else
                NotFound(ctx);
        }
    }


    private static void NotFound(HttpListenerContext ctx)
    {
        using HttpListenerResponse resp = ctx.Response;
        resp.Headers.Set("Content-Type", "text/plain");

        using Stream ros = resp.OutputStream;

        ctx.Response.StatusCode = (int)HttpStatusCode.NotFound;
        ctx.Response.StatusDescription = "404 - Not Found";
        string err = "404 - Not Found";

        byte[] eBuff = Encoding.UTF8.GetBytes(err);
        resp.ContentLength64 = eBuff.Length;

        ros.Write(eBuff, 0, eBuff.Length);
    }

    private static void SendHTML(HttpListenerContext ctx, string path)
    {
        using HttpListenerResponse resp = ctx.Response;
        resp.Headers.Set("Content-Type", "text/html");

        byte[] buffer = File.ReadAllBytes(path);
        resp.ContentLength64 = buffer.Length;

        using Stream ros = resp.OutputStream;
        ros.Write(buffer, 0, buffer.Length);
    }

    private static bool SendImage(HttpListenerContext ctx, string path)
    {
        using HttpListenerResponse resp = ctx.Response;
        resp.Headers.Set("Content-Type", "image/png");

        try
        {
            byte[] buffer = File.ReadAllBytes(path);
        }
        
        catch(Exception ex)
        {
            Console.WriteLine("Error:" + ex.Message);
            return false;
        }

        finally
        {
            resp.ContentLength64 = buffer.Length;
            Console.WriteLine($"{buffer.Length}");
            using Stream ros = resp.OutputStream;
            ros.Write(buffer, 0, buffer.Length);
        }

        return true;
    }
}
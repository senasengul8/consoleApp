using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct SystemInfo
{
    public double cpuUsage;
    public int ramUsage;
    public int hddUsage;
    public double cpuTemperature;
}

public static class NativeMethods
{
    const string DllPath = "C:/Users/nur20/RiderProjects/DynamicLibrary3/DynamicLibrary3/mydll.dll"; // Replace with the actual DLL path

    [DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern SystemInfo getSystemInfo();
}

class Program
{
    static void Main(string[] args)
    {
        while (true)
        {
            SystemInfo info = NativeMethods.getSystemInfo();

            Console.WriteLine($"CPU Usage: {info.cpuUsage}%");
            Console.WriteLine($"RAM Usage: {info.ramUsage} MB");
            Console.WriteLine($"HDD Usage: {info.hddUsage} GB");
            Console.WriteLine($"CPU Temperature: {info.cpuTemperature}°C");

            System.Threading.Thread.Sleep(30000); // Sleep for 30 seconds
        }
    }
}
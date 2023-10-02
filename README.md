# consoleApp
![image1](https://github.com/senasengul8/consoleApp/assets/44581008/0b715c63-8d0f-4fb4-bf80-a468170398ae)


My program works like this, but I can not implement temperature because I have a lot of errors.

Also it works with dotnet run,I used Rider Jet brains development and .NET 7.0 . I prefer doing Console application.

```diff
What I did 
```


I have a C# struct that represents the system information you want to retrieve: CPU usage, RAM usage, HDD usage, and CPU temperature.


Native method: This class provides a platform invocation services (P/Invoke) method to call a method (getSystemInfo) from a native DLL (mydll.dll). The DLL path is specified using the DllImport attribute.

The Program class contains the Main method, which is the entry point of the program. Inside the Main method, it calls the getSystemInfo method from the NativeMethods class to retrieve system information. The information is then displayed on the console every 30 seconds.

How I connect c++ and c#
```diff
I created dll file:
 g++ -shared -o mydll.dll dllmain.cpp -lPdh  
```
```diff
In C++:
```
double getCPUUsage(): This function retrieves CPU usage using the PDH library. It opens a query, adds a counter for CPU usage, collects data, and gets the formatted counter value.


int getRAMUsage(): This function retrieves RAM usage by querying the system's memory status.


int getHDDUsage(): This function retrieves HDD usage by querying the disk space.

#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <Pdh.h>
```diff
For temperature:
```
One common method is to use the Windows Management Instrumentation (WMI) to access temperature-related information

Before using WMI, initialize the Component Object Model (COM) library.
```diff
CoInitializeEx(0, COINIT_MULTITHREADED);


IWbemLocator* pLoc = nullptr;
IWbemServices* pSvc = nullptr;

HRESULT hres = CoCreateInstance(
    CLSID_WbemLocator, nullptr,
    CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<LPVOID*>(&pLoc));

// Check for errors and connect to WMI
if (SUCCEEDED(hres)) {
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, 0, nullptr, 0, 0, &pSvc);
   
}

IEnumWbemClassObject* pEnumerator = nullptr;
hres = pSvc->ExecQuery(
    bstr_t("WQL"), bstr_t("SELECT * FROM Win32_TemperatureProbe"),
    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator

    if (SUCCEEDED(hres)) {
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        // Process the temperature data...
        // Extract the temperature information from pclsObj
    }

    pEnumerator->Release();
}

pSvc->Release();
pLoc->Release();
CoUninitialize();

```
errors on temperature
```diff
 2/12.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\nur20\AppData\Local\Temp\ccsE0HUx.o:dllmain.cpp:(.text+0x55e): undefined reference to `__imp_CoUninitialize'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\nur20\AppData\Local\Temp\ccsE0HUx.o:dllmain.cpp:(.text+0x5d3): undefined reference to `__imp_CoUninitialize'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\nur20\AppData\Local\Temp\ccsE0HUx.o:dllmain.cpp:(.text$_ZN7_bstr_t6Data_tC1EPKc[_ZN7_bstr_t6Data_tC1EPKc]+0x2f): undefined reference to `_com_util::ConvertStringToBSTR(char const*)'
```

I tried 
g++ -shared -o mydll.dll dllmain.cpp -lole32 -lcomsuppw

The -lole32 and -lcomsuppw flags tell the linker to link against the ole32.lib and comsuppw.lib libraries, respectively, but it does not solve issue.






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





#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <Pdh.h>  // Include the PDH header

// Link against the PDH library
#pragma comment(lib, "Pdh.lib")


struct SystemInfo {
    double cpuUsage;        // CPU usage as a percentage (0-100%)
    int ramUsage;           // RAM usage in MB
    int hddUsage;           // HDD usage in GB
    double cpuTemperature;  // CPU temperature in degrees Celsius
};

// Function to get CPU usage
double getCPUUsage() {
    PDH_FMT_COUNTERVALUE counterValue;
    PDH_HCOUNTER counter;

    PdhOpenQuery(NULL, NULL, &counter);
    PdhAddCounterW(counter, L"\\Processor(_Total)\\% Processor Time", NULL, &counter);  // Use PdhAddCounterW for wide strings
    PdhCollectQueryData(counter);
    PdhCollectQueryData(counter);
    PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &counterValue);
    PdhCloseQuery(counter);

    return counterValue.doubleValue;
}



int getRAMUsage() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    return static_cast<int>((memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys) / (1024 * 1024));  // in MB
}

// Function to get HDD usage
int getHDDUsage() {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    GetDiskFreeSpaceEx(NULL, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes);
    return static_cast<int>(totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024));  // in GB
}

// Function to get CPU temperature
double getTemperature() {
    // Implement code to read CPU temperature from appropriate sources for your platform
    // This will depend on your hardware and the methods available to read CPU temperature
    // As an example, we'll just return a simulated temperature
    return 50.0;  // Simulated temperature in degrees Celsius
}

extern "C" __declspec(dllexport) SystemInfo getSystemInfo() {
    SystemInfo info;
    info.cpuUsage = getCPUUsage();
    info.ramUsage = getRAMUsage();
    info.hddUsage = getHDDUsage();
    info.cpuTemperature = getTemperature();

    return info;
}
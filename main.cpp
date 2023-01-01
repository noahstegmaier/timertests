#define WIN32_LEAN_AND_MEAN 
#define NOMINMAX
#include <windows.h>
#include <timeapi.h>
#include <iostream>

int main(){
    TIMECAPS caps;
    timeGetDevCaps(&caps, sizeof(TIMECAPS));
    std::cout << "Min: " << caps.wPeriodMin << "ms\n";
    std::cout << "Max: " << caps.wPeriodMax << "ms\n";
    Sleep(2000);
    timeBeginPeriod(1);
    
    LARGE_INTEGER bogdan;
    LARGE_INTEGER bogdan2;
    QueryPerformanceCounter(&bogdan);
    QueryPerformanceCounter(&bogdan2);
    while (bogdan2.QuadPart == bogdan.QuadPart)
    {
        QueryPerformanceCounter(&bogdan2);
    }
    
    auto diff = bogdan2.QuadPart - bogdan.QuadPart;
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    std::cout << "1:\t" << bogdan.QuadPart << "\n2:\t" << bogdan2.QuadPart << "\nDiff:\t" << diff << "\n" << "Freq:\t" << freq.QuadPart << "Hz\n";
    return 1337;
}
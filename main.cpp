#include <stdint.h>
#include <vcruntime.h>
#define WIN32_LEAN_AND_MEAN 
#define NOMINMAX
#include <windows.h>
#include <timeapi.h>
#include <fmt/core.h>
using fmt::print;

LONGLONG getns(LARGE_INTEGER begin, LARGE_INTEGER end, LARGE_INTEGER freq){
    auto diff = end.QuadPart - begin.QuadPart;
    auto diffns = diff * 1000000000 / freq.QuadPart;
    return diffns;
}

LONGLONG getmicros(LARGE_INTEGER begin, LARGE_INTEGER end, LARGE_INTEGER freq){
    auto diff = end.QuadPart - begin.QuadPart;
    auto diffns = diff * 1000000 / freq.QuadPart;
    return diffns;
}

int main(){
    TIMECAPS caps;
    timeGetDevCaps(&caps, sizeof(TIMECAPS));
    print("Min:\t{}ms\n", caps.wPeriodMin);
    print("Max:\t{}ms\n", caps.wPeriodMax);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    print("Freq:\t{}Hz\n", freq.QuadPart);
    LARGE_INTEGER begin;
    LARGE_INTEGER end;

    QueryPerformanceCounter(&begin);
    Sleep(0);
    QueryPerformanceCounter(&end);
    print("Sleep(0) took {}ns\n", getns(begin, end, freq));
    
    QueryPerformanceCounter(&begin);
    Sleep(1);
    QueryPerformanceCounter(&end);
    print("Sleep(1) took {}μs\n", getmicros(begin, end, freq));

    print("\nUsing timeBeginPeriod(1)...\n\n");
    timeBeginPeriod(1);
    
    QueryPerformanceCounter(&begin);
    Sleep(0);
    QueryPerformanceCounter(&end);
    print("Sleep(0) took {}ns\n", getns(begin, end, freq));
    
    QueryPerformanceCounter(&begin);
    Sleep(1);
    QueryPerformanceCounter(&end);
    print("Sleep(1) took {}μs\n", getmicros(begin, end, freq));

    uint64_t count = 0;
    QueryPerformanceCounter(&begin);
    do
    {
        QueryPerformanceCounter(&end);
        count += 1;
    }while (end.QuadPart == begin.QuadPart);

    
    print("1:\t{}\n", begin.QuadPart);
    print("2:\t{}\n", end.QuadPart);
    auto diff = end.QuadPart - begin.QuadPart;
    print("Diff:\t{}\n", diff);
    print("Count:\t{}\n", count);
    print("Time:\t{}ns\n", getns(begin, end, freq));
    return 0;
}
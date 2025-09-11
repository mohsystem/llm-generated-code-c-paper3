#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/times.h>
#include <unistd.h>
#endif

double getProcessorTimeInSeconds() {
#ifdef _WIN32
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime);

    ULARGE_INTEGER kernelTimeUL, userTimeUL;
    kernelTimeUL.LowPart = kernelTime.dwLowDateTime;
    kernelTimeUL.HighPart = kernelTime.dwHighDateTime;
    userTimeUL.LowPart = userTime.dwLowDateTime;
    userTimeUL.HighPart = userTime.dwHighDateTime;

    return (kernelTimeUL.QuadPart + userTimeUL.QuadPart) / 10000000.0;

#else
    struct tms timeSample;
    clock_t now = times(&timeSample);
    return (double) (timeSample.tms_utime + timeSample.tms_stime) / sysconf(_SC_CLK_TCK);
#endif
}



int main() {
    for (int i = 0; i < 5; i++) {
        printf("Processor Time: %f seconds\n", getProcessorTimeInSeconds());

        #ifdef _WIN32
        Sleep(100); // Windows-specific sleep function
        #else
        usleep(100000); // POSIX-compliant usleep (microseconds)
        #endif
    }
    return 0;
}
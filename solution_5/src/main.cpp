#include <iostream>
#include <string>
#include <cstring>
#include <chrono>

#include "MatchSearcherLauncher.h"

#define DEFAULT_THREADS_COUNT 4

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Not enough arguments!" << std::endl;
        return 1;
    }

    if (strlen(argv[2]) == 0)
    {
        std::cout << "Wrong Mask argument!" << std::endl;
        return 1;
    }

    size_t threadsCount = DEFAULT_THREADS_COUNT;
    if (argc >= 4)
    {
        try
        {
            threadsCount = std::stoi(argv[3]);
        }
        catch (...)
        {
            std::cout << "Wrong ThreadsCount argument!" << std::endl;
            return 1;
        }

        if (threadsCount == 0)
        {
            std::cout << "ThreadsCount can't be zero!" << std::endl;
            return 1;
        }
    }

    auto startTime = std::chrono::steady_clock::now();

    MatchSearcherLauncher launcher;
    launcher.Launch(argv[1], argv[2], threadsCount);

    if (argc >= 5)
    {
        if (*argv[4] == '1')
        {
            auto endTime = std::chrono::steady_clock::now();
            std::cout << "Time mcs: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << std::endl;
        }
    }

    return 0;
}

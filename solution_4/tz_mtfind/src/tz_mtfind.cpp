// tz_mtfind.cpp: определяет точку входа для приложения.
//

#include "tz_mtfind.h"

#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>
#include "stringfinder.h"


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "tz_mtfind.exe <filename> <mask>" << std::endl;
        return -1;
    }
    std::string fname(argv[1]);
    std::string mask(argv[2]);
    int thread_count = 8;
    StringFinder sf(thread_count);
    std::vector<StringFinder::DataOutput> fr = sf.find(fname, mask);
    std::cout << fr.size() << std::endl;
    for (const auto& res : fr)
    {
        std::cout << res.line_num + 1 << " " << res.pos + 1 << " " << res.text << std::endl;
    }
    return 0;
}

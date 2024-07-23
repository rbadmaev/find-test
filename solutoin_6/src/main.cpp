#include <iostream>
#include <thread>

#include "findpatterns.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Error: Incorrect number of parameters." << std::endl;
        std::cout << "Usage: mtfind <file_path> <pattern>" << std::endl;
        return -1;
    }
    std::string filePath = argv[1];
    std::string pattern = argv[2];

    bool fileReaded = true;
    std::vector<std::string> lines = mtfind::GetLinesFromFile(filePath, fileReaded);
    if (!fileReaded) {
        std::cout << "Error: Failed to access the file \""
                  << filePath << "\"." << std::endl;
        return -2;
    }

    size_t threadCount = std::thread::hardware_concurrency();
    auto matches = mtfind::FindPattern(lines, pattern, mtfind::QuestionPatternDetector, threadCount);
    std::cout << matches.size() << std::endl;
    for (const auto & match : matches) {
        std::cout << match.line << " "
                  << match.index << " "
                  << match.result << std::endl;
    }
    return 0;
}

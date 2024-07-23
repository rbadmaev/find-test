#include "utils.h"
#include "fstream"

std::vector<std::string> mtfind::GetLinesFromFile(const std::string &filePath, bool & ok)
{
    std::vector<std::string> lines;
    ok = true;
    std::ifstream fStream(filePath);
    if (!fStream) {
        ok = false;
        return lines;
    }
    std::string line;
    while (std::getline(fStream, line)) {
        lines.push_back(line);
    }
    return lines;
}

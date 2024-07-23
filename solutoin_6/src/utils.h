#pragma once

#include <string>
#include <vector>

namespace mtfind
{
    /**
     * @brief GetLinesFromFile -  Reads lines from a file and returns them as a vector of strings
     * @param filePath - The path of the file to read
     * @param ok - The flag indicating whether the file was read successfully
     * @return std::vector<std::string>
     */
    std::vector<std::string> GetLinesFromFile(const std::string & filePath, bool & ok);
}

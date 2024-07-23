#pragma once

#include "patterns.h"

#include <vector>
#include <string>

namespace mtfind
{
    /**
     * @brief The Match struct - Represents a match found by the FindPattern function
     */
    struct Match {
        size_t line;
        size_t index;
        std::string result;
    };

    /**
     * @brief FindPattern - This function searches for a pattern in a vector of lines using a pattern detector
     *
     * @param lines         - The vector of lines to search in
     * @param pattern       - The pattern to search for
     * @param detector      - The pattern detector function to use
     * @param threadCount   - The number of threads to use for parallel processing
     *
     * @return std::vector<Match>
     */
    std::vector<Match> FindPattern(const std::vector<std::string> & lines,
                                   const std::string & pattern,
                                   PatternDetector detector,
                                   size_t threadCount);
}

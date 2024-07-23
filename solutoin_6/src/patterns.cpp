#include "patterns.h"
#include <iostream>


std::vector<mtfind::DetectorMatch>
mtfind::QuestionPatternDetector(const std::string &line,
                                const std::string &pattern)
{
    std::vector<DetectorMatch> results;
    int patternSize = pattern.size();
    int lineSize = line.size();
    for (int i = 0; i <= lineSize - patternSize; i++) {
        bool match = true;
        for (int j = 0; j < patternSize; j++) {
            if (pattern[j] != '?' && pattern[j] != line[i+j]) {
                match = false;
                break;
            }
        }
        if (match) {
            DetectorMatch match;
            match.index = i + 1;
            match.result = line.substr(i, patternSize);
            results.push_back(match);
            i += patternSize - 1;
        }
    }
    return results;
}

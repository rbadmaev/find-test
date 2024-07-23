#pragma once

#include <functional>
#include <vector>
#include <string>

namespace mtfind
{
    /**
     * @brief The DetectorMatch struct - Represents a match found by a pattern detector
     */
    struct DetectorMatch {
        size_t index;
        std::string result;
    };

    /**
     *  @brief PatternDetector type definition
     *  defines the signature of a pattern detector function
     */
    using PatternDetector = std::function<std::vector<DetectorMatch>(const std::string &, const std::string &)>;

    /**
     * @brief QuestionPatternDetector - Implementation of a pattern detector
     * The pattern can contain a "?" wildcard, which matches any single character
     * @param line - The line to search in
     * @param pattern - The pattern to search for
     * @return std::vector<DetectorMatch>
     */
    std::vector<DetectorMatch> QuestionPatternDetector(const std::string & line,
                                                       const std::string & pattern);
}

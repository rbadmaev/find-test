#include "findpatterns.h"

#include <cassert>
#include <future>
#include <iostream>

using VecConstIt = std::vector<std::string>::const_iterator;
using VecConstRange = std::pair<VecConstIt, VecConstIt>;
using VecConstRanges = std::vector<VecConstRange>;
using RangeMatch = std::pair<VecConstIt, mtfind::DetectorMatch>;

std::vector<RangeMatch>
FindPatternInRange(VecConstRange range, std::string pattern, mtfind::PatternDetector detector)
{
    std::vector<std::pair<VecConstIt, mtfind::DetectorMatch>> res;
    for (VecConstIt it = range.first; it != range.second; ++it) {
        std::vector<mtfind::DetectorMatch> detectorMathces = detector(*it, pattern);
        for (const mtfind::DetectorMatch & match : detectorMathces) {
            res.emplace_back(it, match);
        }
    }
    return res;
}

VecConstRanges LinesToRanges(const std::vector<std::string> & lines,
                             size_t threadCount)
{
    assert(threadCount != 0);
    size_t chunkSize = lines.size() / threadCount;
    if (chunkSize == 0) {
        return {std::make_pair(lines.begin(), lines.end())};
    }
    VecConstRanges ranges;
    VecConstIt start = lines.begin();
    for (size_t i = 0; i < threadCount - 1; i++) {
        VecConstIt end = start + chunkSize;
        ranges.emplace_back(start, end);
        start = end;
    }
    ranges.emplace_back(start, lines.end());
    return ranges;
}

std::vector<mtfind::Match> mtfind::FindPattern(const std::vector<std::string> &lines,
                                               const std::string & pattern,
                                               PatternDetector detector,
                                               size_t threadCount)
{
    assert(threadCount != 0);

    std::vector<mtfind::Match> result;
    if (lines.empty()) return result;

    VecConstRanges ranges = LinesToRanges(lines, threadCount);
    assert(!ranges.empty());

    std::vector<std::future<std::vector<RangeMatch>>> futures;
    for (const VecConstRange & range : ranges) {
        futures.push_back(std::async(std::launch::async,
                                     FindPatternInRange,
                                     range, pattern, detector));
    }
    for (auto & future : futures) {
        auto matches = future.get();
        for (const std::pair<VecConstIt, mtfind::DetectorMatch> & match : matches) {
            result.push_back({
                                 static_cast<size_t>(std::distance(lines.cbegin(), match.first)) + 1,
                                 match.second.index,
                                 match.second.result
                             });
        }
    }
    return result;
}

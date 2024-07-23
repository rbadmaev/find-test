#include <iostream>
#include <cstring>

#include "MatchSearcher.h"

MatchSearcher::MatchSearcher(const MatchSearchParams &params) :
    params(params)
{
}

MatchSearcher::~MatchSearcher()
{
    if (thread.joinable())
    {
        thread.join();
    }
}

void MatchSearcher::Run()
{
    stream.open(params.filePath, std::ios::in | std::ios::binary);

    if (!stream.is_open())
    {
        std::cout << "Can't open file in MatchSearher!" << std::endl;
        return;
    }

    stream.seekg(params.startPos);
    thread = std::thread(&MatchSearcher::Search, this);
}

std::vector<MatchSearchResult> MatchSearcher::GetMatches()
{
    if (thread.joinable())
    {
        thread.join();
    }
    return std::move(matches);
}

size_t MatchSearcher::GetLinesCount()
{
    return linesCount;
}

// Проверяем подстроку на соответствие маске
static inline bool CheckMatch(const std::string &substring, const char *mask)
{
    for (size_t i = 0; i < substring.size(); i++)
    {
        if (mask[i] == '?')
        {
            continue;
        }

        if (substring[i] != mask[i])
        {
            return false;
        }
    }
    return true;
}

// Проверяем линию на соответствие маске
static inline void CheckLine(std::vector<MatchSearchResult> &matches, const std::string &line, const char *mask, const size_t maskSize, const size_t linesCount)
{
    size_t linePos = 0;
    while (linePos + maskSize <= line.size())
    {
        std::string lineSubstring = line.substr(linePos, maskSize);
        if (CheckMatch(lineSubstring, mask))
        {
            matches.emplace_back(MatchSearchResult{std::move(lineSubstring), linesCount, linePos + 1});
            linePos += maskSize;
        }
        else
        {
            linePos++;
        }
    }
}

void MatchSearcher::Search()
{
    size_t maskSize = strlen(params.mask);
    linesCount = 0;
    while ((stream.tellg() != -1) && (stream.tellg() < params.endPos))
    {
        linesCount++;
        std::string fileLine;
        getline(stream, fileLine);
        CheckLine(matches, fileLine, params.mask, maskSize, linesCount);
    };
    stream.close();
}

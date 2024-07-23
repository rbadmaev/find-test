#ifndef MATCHSEARCHER_H_
#define MATCHSEARCHER_H_

#include <fstream>
#include <thread>
#include <string>
#include <vector>

#include "MatchSearchParams.h"
#include "MatchSearchResult.h"

// Ищет в определенном диапазоне файла совпадения по маске
class MatchSearcher
{
public:
    MatchSearcher(const MatchSearchParams &);

    ~MatchSearcher();

    void Run();

    std::vector<MatchSearchResult> GetMatches();
    
    size_t GetLinesCount();

private:
    const MatchSearchParams params;
    std::ifstream stream;
    std::thread thread;
    std::vector<MatchSearchResult> matches;
    size_t linesCount;

    void Search();
};

#endif

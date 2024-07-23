#ifndef MATCHSEARCHERLAUNCHER_H_
#define MATCHSEARCHERLAUNCHER_H_

#include <stddef.h>
#include <memory>
#include <vector>

#include "MatchSearcher.h"

// Параллельно ищет в файле совпадения по маске
class MatchSearcherLauncher
{
public:
    void Launch(const char *filePath, const char *mask, size_t threadsCount);

private:
    std::vector<std::unique_ptr<MatchSearcher>> searchers;

    void RunSearchers();
};

#endif

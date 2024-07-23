#ifndef MATCHSEARCHRESULT_H_
#define MATCHSEARCHRESULT_H_

#include <stddef.h>
#include <string>

struct MatchSearchResult
{
    std::string match;
    size_t line;
    size_t pos;
};

#endif

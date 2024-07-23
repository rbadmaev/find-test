#ifndef MATCHSEARCHPARAMS_H_
#define MATCHSEARCHPARAMS_H_

#include <stddef.h>

struct MatchSearchParams
{
    const char *filePath;
    const char *mask;
    size_t startPos;
    size_t endPos;
};

#endif

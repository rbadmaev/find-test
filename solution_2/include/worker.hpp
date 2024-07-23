#pragma once


#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <condition_variable>
#include <mutex>



using std::mutex, std::string;
class MaskKey;



struct OccurenceRecord
{
    size_t _lineNumber;
    size_t _pos;
    string _occurence;

    OccurenceRecord( size_t lineNumber, size_t pos, string&& occurence)
     : _lineNumber(lineNumber)
     , _pos(pos)
     , _occurence(std::move(occurence))
    {}
};



class Worker
{
public:

    Worker(const MaskKey& key)
        :_maskKey(key)
    {}

    void load(std::ifstream& input);

    using Result = std::list<OccurenceRecord>;
    const Result& getResult() { return _result; }

private:

    void process();
    void check(const string& line);
    std::vector<size_t> find_KMP(const string& line, const string& pattern);
    void checkMask(const string& line, size_t keyPos);

    size_t _partLimit = 2000;
    size_t _memoryLimit = 2'000'000;

    using StringsQueue = std::queue<string>;
    std::queue<StringsQueue> _buffer;
    std::condition_variable _cv;
    std::mutex              _mutex;

    bool _endWork = false;

    const MaskKey& _maskKey;
    size_t _lineNumber = 0;
    Result _result;
};

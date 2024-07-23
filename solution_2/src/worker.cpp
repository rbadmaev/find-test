#include "worker.hpp"

#include <future>
#include <thread>

#include <mask_key.hpp>



void Worker::load(std::ifstream& input)
{
    auto r1 = std::async(std::launch::async, [this](){ process(); } );

    StringsQueue part;
    size_t accum = 0;
    while (!input.eof())
    {
        part.emplace();
        std::string& line = part.back();
        std::getline(input, line);

        accum += line.size();
        if (accum > _partLimit) {
            accum = 0;
            {
                std::lock_guard<mutex> lock(_mutex);
                _buffer.push( std::move(part) );
            }
            _cv.notify_one();

            if (_partLimit * _buffer.size() > _memoryLimit)
                std::this_thread::sleep_for( std::chrono::milliseconds(10) );
        }
    }

    if ( !part.empty() ) {
        std::lock_guard<mutex> lock(_mutex);
        _buffer.push( std::move(part) );
    }
    _endWork = true;
    _cv.notify_one();
}



void Worker::process()
{
    do {
        StringsQueue lines;
        {
            std::unique_lock<mutex> lock(_mutex);
            _cv.wait(lock, [this]{return !_buffer.empty(); } );

            lines = std::move(_buffer.front() );
            _buffer.pop();
        }

        while ( !lines.empty() ) {
            const auto& line = lines.front();
            ++_lineNumber;
            check(line);
            lines.pop();
        }

    } while ( !(_endWork && _buffer.empty()) );
}



// Алгоритм КМП эффективного поиска вхождений подстроки.
std::vector<size_t> Worker::find_KMP(const string& line, const string& pattern)
{
    const size_t length = pattern.length();

    // Сформировать префикс функцию.
    std::vector<int> pf(length);
    pf[0] = 0;
    for (size_t k = 0, i = 1; i < length; ++i)
    {
        while ( (k > 0) && (pattern[i] != pattern[k]) )
            k = pf[k - 1];

        if (pattern[i] == pattern[k])
            ++k;

        pf[i] = k;
    }

    // Найти вхождения.
    std::vector<size_t> positions;
    positions.reserve(15);
    for (size_t k = 0, i = 0; i < line.length(); ++i)
    {
        while ( (k > 0) && (pattern[k] != line[i]) )
            k = pf[k - 1];

        if (pattern[k] == line[i])
            ++k;

        if (k == length) {
            auto pos = i - length + 1;
            positions.push_back(pos);
        }
    }
    return positions;
}



void Worker::check(const string& line)
{
    if (line.length() < _maskKey._mask.length())
        return;

    // Найти вхождения ключа.
    auto keyPositions = find_KMP(line, _maskKey._key);
    if (keyPositions.empty())
        return;

    // Проверить маску для каждого вхождения ключа маски.
    for (auto pos : keyPositions)
        checkMask(line, pos);
}



void Worker::checkMask(const string& line, size_t keyPos)
{
    auto n = line.length();
    auto end = keyPos + _maskKey._length + _maskKey._indent_right;
    bool borderConditions = (keyPos >= _maskKey._indent_left) && end <= n;
    if (!borderConditions)
        return;

    auto begin = keyPos - _maskKey._indent_left;

    // Проверка совпадения по маске.
    for (size_t i = begin, j = 0; i < end; ++i, ++j)
    {
        char c = _maskKey._mask[j];
        if (c == '?')
            continue;
        if (line[i] != c)
            return;
    }

    // Записать совпадение маски.
    _result.emplace_back( _lineNumber, begin,
                          line.substr(begin, end - begin) );
}

#pragma once

#include <string>


/// Ключ маски - самая длинная последовательность между вопросами.
struct MaskKey
{
    size_t _length = 0;         ///< Длина ключа.
    size_t _pos = 0;            ///< Позиция ключа.

    size_t _indent_left = 0;    ///< Расстояние от начала маски.
    size_t _indent_right = 0;   ///< Расстояние до конца маски.

    std::string _key;
    std::string _mask;


    MaskKey(const char* mask)
        : _mask(mask)
    {
        findMaxSequence();

        _key = _mask.substr(_pos, _length);
        _indent_left  = _pos;
        _indent_right = _mask.size() - (_pos + _length);
    }

    void findMaxSequence()
    {
        size_t count(0), n(_mask.size());
        for (size_t i = 0; i < n; ++i)
        {
            if (_mask[i] == '?') {
                if (count == 0)
                    continue;

                if ( count > _length )
                    _length = count, _pos = i - count;
                count = 0;
            } else
                ++count;
        }

        if (count != 0)
            if ( count > _length )
                _length = count, _pos = n - count;
    }
};



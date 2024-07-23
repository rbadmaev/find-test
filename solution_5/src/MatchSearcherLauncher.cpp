#include <iostream>
#include <fstream>

#include "MatchSearcherLauncher.h"

void MatchSearcherLauncher::Launch(const char *filePath, const char *mask, size_t threadsCount)
{
    std::ifstream stream(filePath, std::ios::in | std::ios::binary);

    if (!stream.is_open())
    {
        std::cout << "Can't open file!" << std::endl;
        return;
    }

    stream.seekg(0, std::ios_base::end); // Встаем в конец файла
    size_t totalSymbols = stream.tellg(); // Общее количество символов в файле
    size_t symbolsPerThread = totalSymbols / threadsCount; // Количество символов, которое нужно обработать каждому потоку

    stream.seekg(0, std::ios_base::beg); // Встаем в начало файла
    MatchSearchParams params;
    params.filePath = filePath;
    params.mask = mask;

    for (size_t i = 0; i < threadsCount; i++)
    {
        if (stream.eof())
        {
            break; // Потоков больше, чем строк
        }

        params.startPos = stream.tellg(); // Стартовая позиция соответствует текущей позиции файла
        stream.seekg(symbolsPerThread, std::ios_base::cur); // Перемещаемся вперед на количество выделенных этому потоку символов
        std::string line;
        getline(stream, line); // Перемещаемся до ближайшего конца линии

        if (stream.eof())
        {
            params.endPos = totalSymbols;  // Конечная позиция соответствует общему кол-ву символов, если это последняя позиция файла
        }
        else
        {
            params.endPos = stream.tellg(); // Конечная позиция соответствует текущей позиции файла
        }
        searchers.emplace_back(std::make_unique<MatchSearcher>(params));
    }

    stream.close();
    RunSearchers();
}

void MatchSearcherLauncher::RunSearchers()
{
    for (auto &searcher : searchers)
    {
        searcher->Run(); // Запускаем асинхронный поиск
    }

    size_t totalMatchesCount = 0;
    size_t linesCount = 0;
    std::vector<std::vector<MatchSearchResult>> allMatches;

    for (auto &searcher : searchers)
    {
        auto matches = searcher->GetMatches(); // Совпадения конкретного поисковщика
        totalMatchesCount += matches.size();
        for (auto &match : matches) // Конкретные совпадения
        {
            match.line += linesCount; // Меняем локальный номер линий на глобальный
        }
        linesCount += searcher->GetLinesCount();
        allMatches.emplace_back(std::move(matches));
    }

    // Вывод информации пользователю
    std::cout << totalMatchesCount << std::endl;
    for (auto &threadMatches : allMatches)
    {
        for (auto &match : threadMatches)
        {
            std::cout << match.line << " " << match.pos << " " << match.match << std::endl;
        }
    }
}

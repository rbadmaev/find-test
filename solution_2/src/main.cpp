#include <worker.hpp>
#include <mask_key.hpp>

#include <fstream>
#include <iostream>


using std::cout;



int main(int argc, char* argv[])
{
    // cout << "** mt find ** \n\n";
    cout.precision(3);

    if (argc < 3) {
        cout << "No parameters specified! \n";
        return -1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "input file not found! \n";
        return -1;
    }

    MaskKey key(argv[2]);

    Worker worker(key);
    worker.load(input);
    input.close();

    //
    auto result = worker.getResult();
    cout << result.size() << "\n";
    for (const auto& record : result) {
        cout << record._lineNumber << " "
             << record._pos +1 << " "
             << record._occurence << "\n";
    }

    return 0;
}


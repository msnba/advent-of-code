#include "lib.h"

Lib::Lib(std::string file)
{
    input.open(file);
    if (!input.is_open())
    {
        std::cout << "Input error." << std::endl;
        exit(1);
    }
}

void Lib::ref()
{
    input.clear();
    input.seekg(0, std::ios::beg);
}

std::vector<std::string> Lib::split(const std::string &input, std::string delimiter)
{
    if (!delimiter.length())
        return std::vector<std::string>();

    std::vector<std::string> splitted;

    auto last = input.begin();
    auto found = last;
    while (found != input.end())
    {
        found = std::search(last, input.end(), delimiter.begin(), delimiter.end());
        splitted.push_back(std::string(last, found));
        last = found + delimiter.length();
    }

    return splitted;
}

void Lib::start_timer()
{
    timer = std::chrono::high_resolution_clock::now();
}
long long Lib::end_timer() // milliseconds
{
    std::chrono::high_resolution_clock::time_point tend =
        std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               tend - timer)
        .count();
}
long long Lib::reset_timer()
{
    long long elapsed = Lib::end_timer();
    Lib::start_timer();
    return elapsed;
}

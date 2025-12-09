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

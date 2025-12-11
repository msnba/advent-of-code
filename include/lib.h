#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

class Lib
{
public:
    std::ifstream input;
    std::chrono::high_resolution_clock::time_point timer;

    Lib() = default;
    Lib(std::string file);

    void ref();

    static std::vector<std::string> split(const std::string &input, const std::string delimiter);

    void start_timer();
    long long end_timer();
    long long reset_timer();
};
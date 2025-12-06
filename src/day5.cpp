#include <vector>
#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day5input.txt");

void p1(Lib &l)
{
    int sum = 0;
    string line;
    vector<pair<long, long>> ranges;
    bool cutoff = false;
    while (getline(l.input, line))
    {
        if (line.empty())
        {
            cutoff = true;
            continue;
        }
        if (!cutoff)
        {
            auto parts = Lib::split(line, "-");
            ranges.push_back({stol(parts[0]), stol(parts[1])});
        }
        else
        {
            long id = stol(line);
            bool fresh = false;
            for (auto &r : ranges)
            {
                if (id >= r.first && id <= r.second)
                {
                    fresh = true;
                    break;
                }
            }
            if (fresh)
                sum++;
        }
    }
    cout << sum << endl;
}

void p2(Lib &l)
{
    l.ref();
    long sum2 = 0;
    string line;
    vector<pair<long, long>> ranges;
    while (getline(l.input, line)) // array capture
    {
        if (line.empty())
        {
            break;
        }
        auto parts = Lib::split(line, "-");
        ranges.push_back({stol(parts[0]), stol(parts[1])});
    }

    sort(ranges.begin(), ranges.end());

    vector<pair<long, long>> merged; // pairs largest together so it captures all range
    for (auto &r : ranges)
    {
        if (merged.empty() || r.first > merged.back().second) // if the first value in range is larger than merged back second, that means that the ranges do not overlap
            merged.push_back(r);
        else
            merged.back().second = max(merged.back().second, r.second); // always sorted in ascending order so the only thing needed is extending the ranges
    }

    for (auto &r : merged)
    {
        sum2 += r.second - r.first + 1;
    }
    cout << sum2 << endl;
}

int main()
{
    p1(l);
    p2(l);
    return 0;
}
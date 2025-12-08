#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day8input.txt");

struct j
{
    int x, y, z;
};

double distance(j &a, j &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

void p1(Lib &l)
{
    vector<j> grid;
    string line;
    while (getline(l.input, line))
    {
        if (line.empty())
            continue;
        vector<string> parts = Lib::split(line, ",");
        grid.push_back({stoi(parts[0]), stoi(parts[1]), stoi(parts[2])});
    }

    // connect junctions that are closest together, where they become a circuit
    // loop through grid and find the PAIRS that are closest together, then loop through those pairs and use the rules above to create circuits

    struct pair
    {
        double d2;
        int i, j;
    };

    vector<pair> pairs;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = i + 1; j < grid.size(); j++)
        {
            pairs.push_back({distance(grid[i], grid[j]), i, j});
        }
    }
}
void p2(Lib &l)
{
    l.ref();
}
int main()
{
    p1(l);
    p2(l);
    return 0;
}
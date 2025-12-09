#include <vector>
#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day4input.txt");

void p1(Lib &l)
{
    int rolls = 0;
    vector<string> lines = vector<string>();
    string currentline;
    while (getline(l.input, currentline))
    {
        lines.push_back(currentline);
    }
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] != '@')
                continue;

            int surrounding = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0) // skip current
                        continue;

                    int ni = i + di; // true positions
                    int nj = j + dj;

                    if (ni >= 0 && ni < lines.size() && nj >= 0 && nj < lines[i].size()) // check bounds
                    {
                        if (lines[ni][nj] == '@')
                            surrounding++;
                    }
                }
            }

            if (surrounding < 4)
            {
                rolls++;
            }
        }
    }
    cout << rolls << endl;
}

void p2(Lib &l)
{
    vector<string> lines = vector<string>();
    string currentline;
    while (getline(l.input, currentline))
    {
        lines.push_back(currentline);
    }

    int rolls = 0;

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < lines.size(); i++)
        {
            for (int j = 0; j < lines[i].size(); j++)
            {
                if (lines[i][j] != '@')
                    continue;

                int surrounding = 0;
                for (int di = -1; di <= 1; di++) // 3x3 grid check (excluding center)
                {
                    for (int dj = -1; dj <= 1; dj++)
                    {
                        if (di == 0 && dj == 0)
                            continue;

                        int ni = i + di;
                        int nj = j + dj;

                        if (ni >= 0 && ni < lines.size() && nj >= 0 && nj < lines[i].size() && lines[ni][nj] == '@') // legit just a constraint check
                            surrounding++;
                    }
                }

                if (surrounding < 4)
                {
                    rolls++;
                    lines[i][j] = 'x';
                    changed = true;
                }
            }
        }
    }

    cout << rolls << endl;
}

int main()
{
    // p1(l);
    p2(l);
    return 0;
}
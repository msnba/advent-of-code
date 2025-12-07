#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day7input.txt");

void p1(Lib &l)
{
    long splitnum = 0;

    vector<string> grid;
    vector<int> beams;
    string line;
    while (getline(l.input, line))
        grid.push_back(line);

    for (int col = 0; col < grid[0].size(); col++)
    {
        if (grid[0][col] == 'S')
        {
            grid[1][col] = '|';
            beams.push_back(col);
        }
    }

    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[row].size(); col++)
        {
            vector<int> newbeams;
            if (grid[row][col] == '^' && grid[row - 1][col] == '|')
            {
                if (col - 1 >= 0)
                {
                    grid[row][col - 1] = '|';
                    newbeams.push_back(col - 1);
                }
                if (col + 1 < grid[row].size())
                {
                    grid[row][col + 1] = '|';
                    newbeams.push_back(col + 1);
                }
            }
            else if (row > 0 && grid[row - 1][col] == '|')
            {
                grid[row][col] = '|';
                newbeams.push_back(col);
            }
            if (!newbeams.empty())
                beams = newbeams;
        }
        // cout << grid[row] << endl;
    }
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[row].size(); col++)
        {
            if (grid[row][col] == '|' && row < grid.size() - 1)
            {
                splitnum = (grid[row + 1][col] == '^') ? splitnum + 1 : splitnum;
            }
        }
    }

    cout << splitnum << endl;
}
long long counttimeline(int node, vector<vector<int>> &adj)
{
    if (adj[node].empty())
        return 1;
    long long total = 0;
    for (int next : adj[node])
    {
        total += counttimeline(next, adj);
    }
    return total;
}
long long search(int r, int c, const vector<string> &grid, vector<vector<long long>> &memory)
{
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid.size())
        return 0;
    if (memory[r][c] != -1)
        return memory[r][c];

    char ch = grid[r][c];
    long long total = 0;

    if (ch == '^')
    {
        if (c > 0)
            total += search(r, c - 1, grid, memory);
        if (c + 1 < grid[0].size())
            total += search(r, c + 1, grid, memory);
    }
    else
    {
        if (r + 1 < grid.size())
            total = search(r + 1, c, grid, memory);
        else
            total = 1;
    }
    return memory[r][c] = total;
}
void p2(Lib &l)
{
    l.ref();
    vector<string> grid;
    string line;
    while (getline(l.input, line))
        grid.push_back(line);

    vector<vector<long long>> memory(grid.size(), vector<long long>(grid[0].size(), -1));

    cout << search(0, grid[0].size() / 2, grid, memory) << endl;
}
int main()
{
    p1(l);
    p2(l);
    return 0;
}
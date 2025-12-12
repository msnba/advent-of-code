#include <cmath>
#include <vector>
#include <sstream>
#include "lib.h"
using namespace std;

using Grid = vector<string>;
using Board = vector<vector<int>>;

int W, H;
vector<Grid> shapes;

// backtracking with on-the-fly rotation implementation
Grid rotate90(Grid &g)
{
    int h = g.size();
    int w = g[0].size();
    Grid r(w, string(h, '.'));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (g[i][j] == '#')
                r[j][h - 1 - i] = '#';

    return r;
}

Grid flipH(Grid &g)
{
    Grid r = g;
    for (string &row : r)
        reverse(row.begin(), row.end());
    return r;
}

bool canPlace(Board &b, Grid &g, int bx, int by)
{
    int h = g.size(), w = g[0].size();
    if (bx < 0 || by < 0 || bx + w > W || by + h > H)
        return false;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (g[y][x] == '#' && b[by + y][bx + x] != -1)
                return false;
    return true;
}

void place(Board &b, Grid &g, int bx, int by, int id)
{
    int h = g.size(), w = g[0].size();
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (g[y][x] == '#')
                b[by + y][bx + x] = id;
}

bool solve(Board &b, vector<int> &need)
{
    bool done = true;
    for (int v : need)
        if (v > 0)
        {
            done = false;
            break;
        }
    if (done)
        return true;
    int si = -1;
    for (int i = 0; i < need.size(); i++)
        if (need[i] > 0)
        {
            si = i;
            break;
        }
    need[si]--;

    vector<Grid> orientations;
    Grid cur = shapes[si];
    for (int r = 0; r < 4; r++)
    {
        orientations.push_back(cur);
        orientations.push_back(flipH(cur));
        cur = rotate90(cur);
    }

    for (Grid &g : orientations)
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                if (canPlace(b, g, x, y))
                {
                    place(b, g, x, y, si);
                    if (solve(b, need))
                        return true;
                    place(b, g, x, y, -1);
                }

    need[si]++;
    return false;
}
void p1(Lib &l)
{
    int total = 0;
    string line;

    while (getline(l.input, line))
    {
        // parser work in progress
    }

    cout << total << endl;
}
void p2(Lib &l)
{
    l.ref();
}
int main()
{
    Lib l = Lib("input/day12input.txt");
    l.start_timer();
    p1(l);
    cout << "Elapsed: " << l.reset_timer() << " ms" << endl;
    p2(l);
    cout << "Elapsed: " << l.end_timer() << " ms" << endl;
    return 0;
}
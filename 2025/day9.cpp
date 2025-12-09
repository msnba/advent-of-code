#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day9input.txt");

struct p
{
    int x, y;
};

long long calculateSize(p &a, p &b)
{
    return (long long)(abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1); // cartesian coordinates
}

void p1(Lib &l)
{
    long long highest = 0;
    vector<p> points;
    string line;
    while (getline(l.input, line))
    {
        vector<string> split = Lib::split(line, ",");
        points.push_back({stoi(split[0]), stoi(split[1])});
    }

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            highest = max(highest, calculateSize(points[i], points[j]));
        }
    }

    cout << highest << endl;
}
unordered_map<int, vector<int>> buildInt(const vector<p> &points) // scans all vertical edges of the polygon and records the x coordinates where the edges cross the row
{
    unordered_map<int, vector<int>> crossings; // for each row y, temp store the x-coordinates where edges cross that row

    for (int i = 0; i < points.size(); ++i)
    {
        p a = points[i];
        p b = points[(i + 1) % points.size()];

        if (a.x == b.x) // only consider vertical edges
        {
            int x = a.x;
            int y1 = min(a.y, b.y);
            int y2 = max(a.y, b.y);
            for (int y = y1; y < y2; ++y)
                crossings[y].push_back(x);
        }
    }

    unordered_map<int, vector<int>> intervals; // final map of y values corresponding to x intervals of green tiles
    for (auto &kv : crossings)
    {
        auto &xs = kv.second;
        sort(xs.begin(), xs.end());
        intervals[kv.first] = xs; // store as sorted list; every pair is an interval
    }

    return intervals;
}
bool valid(int xmin, int xmax, int ymin, int ymax,
           unordered_map<int, vector<int>> &intervals) // checks if rect is fully inside of green tiles
{
    for (int y = ymin; y <= ymax; y++)
    {
        auto it = intervals.find(y); // if there are no green intervals for this row, the rectangle is invalid
        if (it == intervals.end())
            return false;

        const auto &xs = it->second; // get the sorted list of x intervals for the row
        int lo = 0;
        for (; lo + 1 < xs.size() && xs[lo + 1] < xmin; lo += 2) // scans pairwise
            ;

        if (lo >= xs.size() || xs[lo] > xmin || xs[lo + 1] < xmax) // if no suitable interval exists, or rectangle does not fully cover xmin xmax, rect is invalid
            return false;
    }
    return true;
}
void p2(Lib &l)
{
    l.ref();
    long long highest = 0;
    vector<p> points;
    string line;
    while (getline(l.input, line))
    {
        vector<string> split = Lib::split(line, ",");
        points.push_back({stoi(split[0]), stoi(split[1])});
    }

    // Build the set of all green tiles 'X', or the straight-line connections between the red tiles. The polygon they form also encloses interior green tiles.
    // buildInt(points) converts the polygon edgs to per-row x-intervals representing all of the green tiles on that row.
    // For every pair of red tiles, treat them as opposite corners of a supposed rectangle.
    // Check whether every tile inside of that rectangle is allowed.

    auto intervals = buildInt(points);

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            int xmin = min(points[i].x, points[j].x);
            int xmax = max(points[i].x, points[j].x);
            int ymin = min(points[i].y, points[j].y);
            int ymax = max(points[i].y, points[j].y);

            if (!valid(xmin, xmax, ymin, ymax, intervals))
                continue;

            long long area = 1LL * ((xmax - xmin) + 1) * ((ymax - ymin) + 1); // this bug took me a while, cartesian coordinates oops
            highest = max(highest, area);
        }
    }
    cout << highest << endl;
}
int main()
{
    p1(l);
    p2(l);
    return 0;
}
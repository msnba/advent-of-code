#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <map>
#include "lib.h"
using namespace std;

// state is represented as a bitmask integer
// pressing a button is xor
// search from 0 to target state
long solveMinPresses(int target, int numlights, vector<int> &buttons)
{
    vector<pair<int, int>> q;
    size_t headIdx = 0;
    q.push_back({0, 0});

    vector<bool> visited(1 << numlights, false); // 2^numlights
    visited[0] = true;
    while (headIdx < q.size())
    {
        pair<int, int> current = q[headIdx++];

        int state = current.first;
        int steps = current.second;

        for (int btnMask : buttons) // brute force every button
        {
            // XOR toggles the bits that are set in the button mask
            int next = state ^ btnMask;

            if (next == target)
            {
                return steps + 1;
            }

            if (!visited[next])
            {
                visited[next] = true;
                q.push_back({next, steps + 1});
            }
        }
    }
    return 0;
}

void p1(Lib &l)
{
    // Each line contains a single indicator light diagram in [square brackets], one or more button wiring schematics in (parentheses), and joltage requirements in {curly braces}.
    // a button wiring schematic like (0,3,4) means that each time you push that button, the first, fourth, and fifth indicator lights would all toggle between on and off. If the indicator lights were [#.....], pushing the button would change them to be [...##.] instead.

    long total = 0;

    string line;
    while (getline(l.input, line))
    {
        vector<string> parts = Lib::split(line, " ");

        string diagram = parts[0].substr(1, parts[0].length() - 2);
        int numLights = diagram.length();
        int targetMask = 0; // goal state

        for (int i = 0; i < numLights; i++)
            if (diagram[i] == '#')
                targetMask |= (1 << i); // literally just builds an exact mirror where 0 corresponds to off and 1 corresponds to on

        vector<int> buttons;

        for (size_t i = 1; i < parts.size() - 1; i++) // skips joltage and beginning
        {
            string token = parts[i];

            vector<string> indices = Lib::split(token.substr(1, token.length() - 2), ","); // over complicated split by comma

            int btnMask = 0; // parsed into single bitmask
            for (string &idx : indices)
                btnMask |= (1 << stoi(idx)); // generates another power of two where only bit at light index is set
            buttons.push_back(btnMask);
        }

        total += solveMinPresses(targetMask, numLights, buttons);
    }
    cout << total << endl;
}
long solveMinPressesGF2(vector<int> &target, int n, const vector<vector<int>> &buttons)
{
    // solve ax=b for a minimal sum(x) over integers using BFS
    map<vector<int>, long> dp;
    vector<int> start(n, 0);
    dp[start] = 0;

    queue<vector<int>> q;
    q.push(start);
    while (!q.empty())
    {
        vector<int> cur = q.front();
        q.pop();
        long cursteps = dp[cur];
        if (cur == target)
            return cursteps;
        for (size_t i = 0; i < buttons.size(); i++)
        {
            vector<int> next = cur;
            for (size_t j = 0; j < buttons[i].size(); j++)
            {
                int idx = buttons[i][j];
                next[idx] += 1; // increment affected counters
            }
            if (dp.find(next) == dp.end() || dp[next] > cursteps + 1)
            {
                dp[next] = cursteps + 1;
                q.push(next);
            }
        }
    }
    return 0;
}
long long totalTime = 0;
void p2(Lib &l)
{
    l.ref();
    long total = 0;
    string line;
    int linen = 0;

    while (getline(l.input, line))
    {
        vector<string> parts = Lib::split(line, " ");

        string joltStr = parts[parts.size() - 1];
        vector<string> joltNums = Lib::split(joltStr.substr(1, joltStr.length() - 2), ",");
        vector<int> target;
        for (int i = 0; i < joltNums.size(); i++)
            target.push_back(stoi(joltNums[i]));
        int n = target.size();

        vector<vector<int>> buttons;
        for (int i = 1; i < parts.size() - 1; i++)
        {
            string token = parts[i];
            vector<string> indices = Lib::split(token.substr(1, token.length() - 2), ",");
            vector<int> btn;
            for (size_t j = 0; j < indices.size(); j++)
                btn.push_back(stoi(indices[j]));
            buttons.push_back(btn);
        }

        total += solveMinPressesGF2(target, n, buttons);

        long long temp = l.reset_timer();
        cout << "Time for line " << linen++ << ": " << temp << " ms" << endl;
        totalTime += temp;
    }

    cout << total << endl;
}
int main()
{
    Lib l = Lib("input/day10input.txt");
    l.start_timer();
    p1(l);
    cout << "Elapsed: " << l.reset_timer() << " ms" << endl;
    p2(l);
    cout << "Elapsed: " << totalTime << " ms" << endl;

    return 0;
}
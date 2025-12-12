#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <map>
#include "lib.h"
#include <functional>
#include <queue>
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
// ts beautiful implementation https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory/ cuz i partly gave up
string key(const vector<int> &p) // convert pattern to key
{
    string key = "";
    for (int i = 0; i < p.size(); ++i)
    {
        key += to_string(p[i]) + ",";
    }
    return key;
}
void comb(int start,
          int k,
          vector<int> &current,
          const vector<vector<int>> &coeffs,
          map<vector<int>, int> &out)
{
    int num_buttons = coeffs.size();
    int num_variables = coeffs[0].size();

    if (k == 0)
    {
        vector<int> pattern(num_variables, 0);
        // sum column-wise how many times each variable is toggled
        for (int idx : current)
            for (int i = 0; i < num_variables; ++i)
                pattern[i] += coeffs[idx][i];

        // out maps pattern to min button count for producing that pattern once
        if (!out.count(pattern))
            out[pattern] = (int)current.size();
        return;
    }

    for (int i = start; i <= num_buttons - k; ++i)
    {
        current.push_back(i);
        comb(i + 1, k - 1, current, coeffs, out);
        current.pop_back();
    }
}

// go over all possible patterns from pressing any subset of buttons
// each pattern [i] = number of presses affecting variable i

map<vector<int>, int> patterns(vector<vector<int>> &coeffs)
{
    map<vector<int>, int> out;
    int num_buttons = coeffs.size();

    for (int len = 0; len <= num_buttons; ++len)
    {
        vector<int> current;
        comb(0, len, current, coeffs, out);
    }

    return out;
}

int solve_single_aux(const vector<int> &g,
                     const map<vector<int>, int> &pattern_costs,
                     map<string, int> &memo)
{
    // base
    bool zero = true;
    for (int v : g)
    {
        if (v != 0)
        {
            zero = false;
            break;
        }
    }
    if (zero)
        return 0;

    // mem check
    string gkey = key(g);
    if (memo.find(gkey) != memo.end())
        return memo[gkey];

    int answer = 1000000;

    map<vector<int>, int>::const_iterator it;
    for (it = pattern_costs.begin(); it != pattern_costs.end(); ++it)
    {
        const vector<int> &pattern = it->first;
        int pattern_cost = it->second;

        bool valid = true;
        vector<int> new_goal(g.size(), 0);

        // validate parity and mag
        for (size_t i = 0; i < g.size(); ++i)
        {
            if (pattern[i] > g[i] || (pattern[i] % 2 != g[i] % 2))
            {
                valid = false;
                break;
            }
            new_goal[i] = (g[i] - pattern[i]) / 2;
        }

        if (valid)
        {
            int candidate =
                pattern_cost + 2 * solve_single_aux(new_goal, pattern_costs, memo);
            if (candidate < answer)
                answer = candidate;
        }
    }

    memo[gkey] = answer;
    return answer;
};

// recursive halfing strategy
// coeffs = button to variable matrix
// goal = target voltages

int solve_single(vector<vector<int>> &coeffs, const vector<int> &goal)
{
    // precompute all patterns reachable by pressing each button 0/1 times
    map<vector<int>, int> pattern_costs = patterns(coeffs);
    map<string, int> memo;

    return solve_single_aux(goal, pattern_costs, memo);
}

int solve(const vector<int> &target, const vector<vector<int>> &buttons)
{
    vector<vector<int>> coeffs;
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        vector<int> row(target.size(), 0);
        for (size_t j = 0; j < buttons[i].size(); ++j)
        {
            int idx = buttons[i][j];
            if (idx >= 0 && idx < static_cast<int>(target.size()))
            {
                row[idx] = 1;
            }
        }
        coeffs.push_back(row);
    }

    return solve_single(coeffs, target);
}
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

        total += solve(target, buttons);
    }

    cout << total << endl;
}
int main()
{
    Lib l = Lib("input/day10input.txt");
    l.start_timer();
    p1(l);
    cout << "Elapsed: " << (double)l.reset_timer() << " ms" << endl;
    p2(l);
    cout << "Elapsed: " << (double)l.reset_timer() << " ms" << endl;

    return 0;
}
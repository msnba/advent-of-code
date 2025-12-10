#include <cmath>
#include <unordered_map>
#include "lib.h"
using namespace std;

struct machine
{
    vector<int> indicators;
    vector<vector<int>> buttons;
};

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

        for (size_t i = 1; i < parts.size(); i++) // skips joltage and beginning
        {
            string token = parts[i];
            if (token.empty() || token[0] == '{')
                break;

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
void p2(Lib &l)
{
    l.ref();
    long total = 0;

    vector<vector<int>> buttons;

    string line;
    while (getline(l.input, line)) // i can see that ts is not a xor bitmask 😭
    {
        vector<string> parts = Lib::split(line, " ");
        for (int i = 1; i < parts.size() - 1; i++)
        {
            vector<int> button;
            for (char c : parts[i])
                if (c != '(' && c != ')' && c != ',')
                    button.push_back(c - '0');

            buttons.push_back(button);
        } // bfs?????
    }
}
int main()
{
    Lib l = Lib("input/day10input.txt");
    p1(l);
    p2(l);
    return 0;
}
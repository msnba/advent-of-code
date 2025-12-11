#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include "lib.h"
using namespace std;

long search(const string &node, unordered_map<string, vector<string>> &nodes)
{
    if (node == "out")
        return 1;
    long total = 0;
    for (string &next : nodes[node])
    {
        total += search(next, nodes);
    }
    return total;
}
void p1(Lib &l)
{
    unordered_map<string, vector<string>> nodes;
    long total = 0;

    string line;
    while (getline(l.input, line))
    {
        vector<string> temp = Lib::split(line, " ");

        string name = temp[0].substr(0, temp[0].size() - 1);

        vector<string> outputs;
        for (int i = 1; i < temp.size(); i++)
            outputs.push_back(temp[i]);
        nodes[name] = outputs;
    }

    cout << search("you", nodes) << endl;
}
map<pair<string, pair<bool, bool>>, long> cache; // i did ts for one of the other problems dw bout it, it just stores which problems were computed so my computer doesnt catch on fire
long search_mod(const string &node, unordered_map<string, vector<string>> &nodes, pair<bool, bool> visited)
{
    static map<pair<string, pair<bool, bool>>, long> cache; // its gotta be static so it stays during recursion

    if (node == "dac")
        visited.first = true;
    if (node == "fft")
        visited.second = true;

    pair<string, pair<bool, bool>> key(node, {visited.first, visited.second});
    if (cache.count(key)) // if it exists in the map return it to save from having to recompute it
        return cache[key];

    if (node == "out") // base case
        return cache[key] = (visited.first && visited.second) ? 1 : 0;

    long total = 0;
    for (string &next : nodes[node])
        total += search_mod(next, nodes, visited);

    return cache[key] = total; // assigns the problem to an answer in the map so it can be grabbed at a later date
}
void p2(Lib &l)
{
    l.ref();
    unordered_map<string, vector<string>> nodes;
    long total = 0;

    string line;
    while (getline(l.input, line))
    {
        vector<string> temp = Lib::split(line, " ");

        string name = temp[0].substr(0, temp[0].size() - 1);

        vector<string> outputs;
        for (int i = 1; i < temp.size(); i++)
            outputs.push_back(temp[i]);
        nodes[name] = outputs;
    }

    cout << search_mod("svr", nodes, {false, false}) << endl;
}
int main()
{
    Lib l = Lib("input/day11input.txt");
    l.start_timer();
    p1(l);
    cout << "Elapsed: " << l.reset_timer() << " ms" << endl;
    p2(l);
    cout << "Elapsed: " << l.end_timer() << " ms" << endl;
    return 0;
}
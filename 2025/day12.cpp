#include <cmath>
#include <vector>
#include "lib.h"
using namespace std;

void p1(Lib &l)
{
    int total = 0;
    string line;

    int linen = 0;
    while (getline(l.input, line))
    {
        if (line.find('x') != string::npos) // if x is in the line
        {
            vector<string> parts = Lib::split(line, " ");
            string dims = parts[0];

            if (dims.back() == ':')
                dims.pop_back();

            vector<string> wh = Lib::split(dims, "x");

            int amt = 0;
            for (int i = 1; i < parts.size(); i++)
                amt += stoi(parts[i]);

            int blocks = (stoi(wh[0]) / 3) * (stoi(wh[1]) / 3);

            if (amt <= blocks)
                total++;
        }
    }

    cout << total << endl;
}
int main()
{
    Lib l = Lib("input/day12input.txt");
    l.start_timer();
    p1(l);
    cout << "Elapsed: " << l.reset_timer() << " ms" << endl;
    // end of year 🥳
    return 0;
}
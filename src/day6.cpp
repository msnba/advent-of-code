#include <cmath>
#include "lib.h"
using namespace std;

Lib l = Lib("input/day6input.txt");

void p1(Lib &l)
{
    long long sum = 0;
    string line;
    vector<vector<int>> grid;
    vector<char> grid_ops;

    while (getline(l.input, line))
    {
        vector<string> split = Lib::split(line, " ");
        vector<int> digits;
        for (int i = 0; i < split.size(); i++)
        {
            if (isdigit(split[i][0]))
            {
                digits.push_back(stoi(split[i]));
            }
            else if (!split[i].empty()) // means we are dealing with ops line
            {
                grid_ops.push_back(split[i][0]);
            }
        }
        if (!digits.empty())
            grid.push_back(digits);
    }

    for (int i = 0; i < grid_ops.size(); i++)
    {
        long long temp = (grid_ops[i] == '+') ? 0 : 1;

        for (int j = 0; j < grid.size(); j++)
        {
            temp = (grid_ops[i] == '+') ? temp + grid[j][i] : temp * grid[j][i];
        }

        sum += temp;
    }

    cout << sum << endl;
}
void p2(Lib &l)
{
    l.ref();
    long long sum = 0;
    string line;
    size_t width = 0;
    vector<string> grid;

    while (getline(l.input, line))
    {
        grid.push_back(line);

        width = max(line.size(), width);
    }

    for (string row : grid) // resize as whitespace defines columns
        row.resize(width, ' ');

    vector<long long> nums; // data for current block
    char op;                // current block operator

    for (int i = width - 1; i >= -1; i--) //-1 forces processing of final leftmost block
    {
        bool seperator = true;

        for (string row : grid) // check for seperator
            if (i >= 0 && row[i] != ' ')
                seperator = false;

        if (seperator) // use whitespace as collection bin
        {
            long long temp = (op == '+') ? 0 : 1;

            for (long long num : nums)
            {
                if (op == '+')
                    temp += num;
                else if (op == '*')
                    temp *= num;
            }

            sum += temp;
            nums.clear();
            op = ' ';
        }
        else
        {
            string builder;
            for (int j = 0; j < grid.size() - 1; j++)
                if (isdigit(grid[j][i]))
                    builder += grid[j][i];

            nums.push_back(stoll(builder));

            char temp = grid.back()[i];
            op = (temp == '+' || temp == '*') ? temp : op;
        }
    }

    cout << sum << endl;
}
int main()
{
    p1(l);
    p2(l);
    return 0;
}
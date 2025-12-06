#include <cmath>
using namespace std;

#include "lib.h"
Lib l;

int p1()
{
    l = Lib("input/day3input.txt");
    string line;
    int sum = 0;
    while (getline(l.input, line)) // brute force
    {
        int maxVal = 0;
        for (int i = 0; i < line.size(); i++)
        {
            int d1 = line[i] - '0';
            for (int j = i + 1; j < line.size(); j++)
            {
                int d2 = line[j] - '0';
                int val = d1 * 10 + d2;
                if (val > maxVal)
                    maxVal = val;
            }
        }
        sum += maxVal;
    }

    return sum;
}
long long p2()
{
    l = Lib("day3input.txt");
    string line;
    long long sum = 0;
    while (getline(l.input, line))
    {
        long long result = 0;
        int start = 0;
        for (int sizeCounter = 12; sizeCounter > 0; sizeCounter--) // in place to count top 12
        {
            int max = 0;                                             // using characters to build output easier
            int pos = start;                                         // index of max
            for (int i = start; i <= line.size() - sizeCounter; i++) // greedy algorithm that finds largest digit in terms of not going over size limit
            {
                if (line[i] - '0' > max)
                {
                    max = line[i] - '0';
                    pos = i;
                }
            }
            result += max * static_cast<long long>(pow(10, sizeCounter - 1));
            start = pos + 1; // the digits have to be in order l->r
        }
        sum += result; // i hate large numbers
    }

    return sum;
}
int main()
{
    cout << p1() << endl;
    cout << p2() << endl;
    return 0;
}
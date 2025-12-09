#include <iostream>
#include <fstream>
#include <string>

int a(int part);

int main()
{
    std::cout << a(1) << std::endl;
    std::cout << a(2) << std::endl;

    return 0;
}
int a(int part)
{
    int count = 0;
    int index = 50;
    int current = 0;
    char turn;

    std::ifstream input("input/day1input.txt");
    if (!input.is_open())
        return 1;
    if (part == 1)
    {
        while (input >> turn >> current)
        {
            if (turn == 'R')
            {
                index = (index + current) % 100;
            }
            else
            {
                index = (index - current) % 100;
                if (index < 0)
                    index += 100;
            }
            if (index == 0)
                count++;
        }
    }
    else
    {
        while (input >> turn >> current)
        {
            if (turn == 'R')
            {
                int a = index + current;
                count += a / 100;
                index = a % 100;
            }
            else
            {
                if (index == 0)
                {
                    count += current / 100;
                }
                else if (current < index)
                {
                }
                else
                {
                    count += (current - index) / 100 + 1;
                }
                int a = (index - current) % 100;
                if (a < 0)
                    a += 100;
                index = a;
            }
        }
    }

    return count;
}
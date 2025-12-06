#include <iostream>
#include <fstream>
#include <string>
using namespace std;

long p2()
{
    std::ifstream input("input/day2input.txt");
    if (!input.is_open())
        return -1;

    long long total = 0;
    long long l, r;
    char dash, comma;
    while (input >> l >> dash >> r)
    {
        // comma fix
        input >> comma;
        if (comma != ',')
            input.unget();

        for (long n = l; n <= r; ++n)
        { // loop through range
            std::string s = std::to_string(n);
            // cout<<s<<endl;
            bool found = false;
            int size = s.size();
            for (int len = 1; len <= size / 2 && !found; ++len)
            {
                if (size % len == 0)
                { // cant be odd
                    std::string temp = s.substr(0, len);
                    bool ok = true;

                    for (int i = len; i < size; i += len)
                    {
                        if (s.substr(i, len) != temp)
                        {
                            ok = false;
                            break;
                        }
                    }
                    if (ok)
                    {
                        total += n;
                        // std::cout << "FOUND: " << n << std::endl;
                        found = true; // break to avoid double counting
                    }
                }
            }
        }
    }
    return total;
}
long p1()
{
    std::ifstream input("day2input.txt");
    if (!input.is_open())
        return -1;

    long long total = 0;
    long long l, r;
    char dash, comma;
    while (input >> l >> dash >> r)
    {
        // comma fix
        input >> comma;
        if (comma != ',')
            input.unget();

        for (long n = l; n <= r; ++n)
        { // loop through range
            std::string s = std::to_string(n);
            // cout<<s<<endl;
            if (s.size() % 2 == 0)
            {
                int half = s.size() / 2;
                if (s.substr(0, half) == s.substr(half))
                {
                    total += n;
                }
            }
        }
    }
    return total;
}
int main()
{
    // std::cout << p1() << std::endl;
    std::cout << p2() << std::endl;

    return 0;
}
#include <cmath>
#include <vector>
#include "lib.h"
using namespace std;

void p1(Lib &l)
{
}
void p2(Lib &l)
{
    l.ref();
}
int main()
{
    Lib l = Lib("input/day12input.txt");
    p1(l);
    p2(l);
    return 0;
}
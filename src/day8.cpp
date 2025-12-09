#include <cmath>
#include <map>
#include <algorithm>
#include <functional>
#include "lib.h"
#include <numeric>
#include <unordered_set>
using namespace std;

Lib l = Lib("input/day8input.txt");

struct DSU
{
    vector<int> parent, sz;
    DSU(int n) : parent(n), sz(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
    bool unite_if_new(int a, int b) // used for p2
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    vector<int> compSizes()
    {
        vector<int> out;
        for (int i = 0; i < parent.size(); ++i)
            if (find(i) == i)
                out.push_back(sz[i]);
        return out;
    }
};
struct Pair
{
    int a, b;
    long long d;
};
void p1(Lib &l)
{
    vector<array<int, 3>> boxes;
    string line;
    while (getline(l.input, line))
    {
        vector<string> parts = Lib::split(line, ",");
        boxes.push_back({stoi(parts[0]), stoi(parts[1]), stoi(parts[2])});
    }

    int n = boxes.size();

    vector<Pair> pairs;
    pairs.reserve((size_t)n * (n - 1) / 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            long long dx = (long long)boxes[i][0] - boxes[j][0];
            long long dy = (long long)boxes[i][1] - boxes[j][1];
            long long dz = (long long)boxes[i][2] - boxes[j][2];
            long long dist2 = dx * dx + dy * dy + dz * dz;
            pairs.push_back({i, j, dist2});
        }
    }

    sort(pairs.begin(), pairs.end(), [](const Pair &A, const Pair &B)
         {
        if (A.d != B.d) return A.d < B.d;
        if (A.a != B.a) return A.a < B.a;
        return A.b < B.b; });

    int K = 1000;
    K = min(K, (int)pairs.size());

    DSU uf(n);
    for (int i = 0; i < K; i++)
    {
        uf.unite(pairs[i].a, pairs[i].b);
    }

    auto sizes = uf.compSizes();
    sort(sizes.begin(), sizes.end(), greater<int>());

    long long prod = 1;
    for (int i = 0; i < 3 && i < (int)sizes.size(); ++i)
        prod *= sizes[i];

    cout << prod << endl;
}
void p2(Lib &l)
{
    l.ref();
    vector<array<int, 3>> boxes;
    string line;
    while (getline(l.input, line))
    {
        vector<string> parts = Lib::split(line, ",");
        boxes.push_back({stoi(parts[0]), stoi(parts[1]), stoi(parts[2])});
    }

    int n = boxes.size();

    vector<Pair> pairs;
    pairs.reserve((size_t)n * (n - 1) / 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            long long dx = (long long)boxes[i][0] - boxes[j][0];
            long long dy = (long long)boxes[i][1] - boxes[j][1];
            long long dz = (long long)boxes[i][2] - boxes[j][2];
            long long dist2 = dx * dx + dy * dy + dz * dz;
            pairs.push_back({i, j, dist2});
        }
    }

    sort(pairs.begin(), pairs.end(), [](const Pair &A, const Pair &B)
         {
        if (A.d != B.d) return A.d < B.d;
        if (A.a != B.a) return A.a < B.a;
        return A.b < B.b; });

    int K = 1000;
    K = min(K, (int)pairs.size());

    DSU uf(n);
    int components = n;
    long long product = 0;

    for (size_t idx = 0; idx < pairs.size(); ++idx)
    {
        int a = pairs[idx].a;
        int b = pairs[idx].b;
        if (uf.unite_if_new(a, b))
        {
            components--;
            if (components == 1)
            {
                product = 1LL * boxes[a][0] * boxes[b][0];
                cout << product << "\n";
                return;
            }
        }
    }
}
int main()
{
    p1(l);
    p2(l);
    return 0;
}
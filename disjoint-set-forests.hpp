#include <vector>
#include "disjoint-set.hpp"

// disjoint set template with union by rank and path compression
template <typename T>
struct ForestsDisjointSet : DisjointSet
{
    std::vector<T> parent;
    std::vector<int> rank;

    DisjointSet(int n) override
    {
        DisjointSet::size = n;
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    T find(T x) override
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(T x, T y) override
    {
        T root_x = find(x);
        T root_y = find(y);
        if (root_x == root_y)
            return;
        if (rank[root_x] < rank[root_y])
            parent[root_x] = root_y;
        else if (rank[root_x] > rank[root_y])
            parent[root_y] = root_x;
        else
        {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
        DisjointSet::size--;
    }
};

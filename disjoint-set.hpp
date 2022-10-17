#include <vector>

// disjoint set abstract template
template <typename T>
struct DisjointSet
{
    virtual T find(T x) = 0;

    virtual void unite(T x, T y) = 0;

    // check if x and y are in the same set
    bool same(T x, T y)
    {
        if (x == y)
            return true;
        return find(x) == find(y);
    }
};

// disjoint set template with union by rank and path compression
template <typename T>
struct ForestsDisjointSet : DisjointSet<T>
{
    std::vector<T> parent;
    std::vector<int> rank;

    ForestsDisjointSet(int n)
    {
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
    }
};

//TODO: disjoint set template using linked list
template <typename T>
struct ListDisjointSet : DisjointSet<T>
{

    ListDisjointSet(int n)
    {

    }

    T find(T x) override
    {
        
    }

    void unite(T x, T y) override
    {
        
    }
};
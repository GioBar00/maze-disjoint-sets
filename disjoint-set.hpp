// disjoint set abstract template
template <typename T>
struct DisjointSet
{
    int size;
    virtual DisjointSet(int n) = 0;

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

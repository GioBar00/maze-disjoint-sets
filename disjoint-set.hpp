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
        while (x != parent[x])
        {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
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

// set for disjoint set using linked list
template <typename T>
struct Set;

// node for disjoint set with linked list
template <typename T>
struct Node
{
    T data;
    Node<T> *next;
    Set<T> *set;
};

template <typename T>
struct Set
{
    Node<T> *head;
    Node<T> *tail;
};

//TODO: disjoint set template using linked list
template <typename T>
struct ListDisjointSet : DisjointSet<T>
{
    std::vector<Node<T> *> nodes;

    ListDisjointSet(int n)
    {
        nodes.resize(n);
        for (int i = 0; i < n; i++)
        {
            Node<T> *node = new Node<T>;
            node->data = i;
            node->next = nullptr;
            node->set = new Set<T>;
            node->set->head = node;
            node->set->tail = node;
            nodes[i] = node;
        }
    }

    T find(T x) override
    {
        return nodes[x]->set->head->data;
    }

    void unite(T x, T y) override
    {
        Node<T> *node_x = nodes[x];
        Node<T> *node_y = nodes[y];
        if (node_x->set == node_y->set)
            return;
        node_x->set->tail->next = node_y->set->head;
        node_x->set->tail = node_y->set->tail;
        Node<T> *node = node_y->set->head;
        while (node != nullptr)
        {
            node->set = node_x->set;
            node = node->next;
        }
    }
};
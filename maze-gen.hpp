#include <vector>
#include <random>
#include "disjoint-set.hpp"

// edge template
template <typename T>
struct Edge
{
    T from;
    T to;
};

// graph template (edge list)
template <typename T>
struct Graph
{
    int n; // number of nodes
    std::vector<Edge<T> > edges;
};

static std::random_device rd;
static std::mt19937 gen(rd());

// random maze generator with disjoint set
template <typename T>
Graph<T> randomMaze(DisjointSet<T> &ds, int rows, int columns)
{

    // create graph
    Graph<T> graph;
    graph.n = rows * columns;

    // random number generator
    std::uniform_int_distribution<> rnd(0, rows * columns - 1);

    int start = 0;
    int end = rows * columns - 1;
    
    while (!ds.same(start, end))
    {
        // generate random cell
        int cell = rnd(gen);
        // generate random direction
        int direction = rnd(gen) % 4;
        // generate adjacent cell in the direction
        int adjacent = cell;
        switch (direction)
        {
            // left
            case 0:
                if (cell % columns != 0)
                    adjacent--;
                break;
            // right
            case 1:
                if (cell % columns != columns - 1)
                    adjacent++;
                break;
            // up
            case 2:
                if (cell >= columns)
                    adjacent -= columns;
                break;
            // down
            case 3:
                if (cell < rows * columns - columns)
                    adjacent += columns;
                break;
        }
        // remove wall between cell and adjacent
        if (!ds.same(cell, adjacent)) 
        {
            ds.unite(cell, adjacent);
            // generate edge
            Edge<T> edge;
            edge.from = cell;
            edge.to = adjacent;
            graph.edges.push_back(edge);
        }

    }

    return graph;
    
}

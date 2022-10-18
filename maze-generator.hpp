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
void randomMaze(DisjointSet<T> &ds, int rows, int columns)
{
    // random number generator
    std::uniform_int_distribution<> rnd(0, rows * columns - 1);

    int start = 0;
    int end = rows * columns - 1;

    while (!ds.same(start, end))
    {
        // generate random cell
        int cell = rnd(gen);
        // generate adjacent cell in the direction
        int adjacent = cell;
        // remove not available directions
        int availableDirections[4] = {0, 1, 2, 3};
        int availableDirectionsCount = 4;
        if (cell % columns == 0)
        {
            availableDirections[0] = -1;
            availableDirectionsCount--;
        }
        if (cell % columns == columns - 1)
        {
            availableDirections[1] = -1;
            availableDirectionsCount--;
        }
        if (cell < columns)
        {
            availableDirections[2] = -1;
            availableDirectionsCount--;
        }
        if (cell >= rows * columns - columns)
        {
            availableDirections[3] = -1;
            availableDirectionsCount--;
        }

        // generate random direction
        int direction = rnd(gen) % availableDirectionsCount;
        for (int i = 0; i < 4; i++)
        {
            if (availableDirections[i] == -1)
                continue;
            if (direction == 0)
            {
                direction = i;
                break;
            }
            direction--;
        }

        switch (direction)
        {
        // left
        case 0:
            adjacent--;
            break;
        // right
        case 1:
            adjacent++;
            break;
        // up
        case 2:
            adjacent -= columns;
            break;
        // down
        case 3:
            adjacent += columns;
            break;
        }

        // remove wall between cell and adjacent
        if (!ds.same(cell, adjacent))
            ds.unite(cell, adjacent);
    }
}

/*
template <typename T>
Graph<T> randomMaze(Graph<T> fullGraph, DisjointSet<T> &ds, int rows, int columns)
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
        // get random edge
        int edgeIndex = rnd(gen) % fullGraph.edges.size();
        Edge<T> edge = fullGraph.edges[edgeIndex];
        // remove edge from full graph
        fullGraph.edges.erase(fullGraph.edges.begin() + edgeIndex);


        // remove wall between cell and adjacent
        if (!ds.same(edge.from, edge.to))
        {
            ds.unite(edge.from, edge.to);
            // generate edge
            graph.edges.push_back(edge);
        }
    }

    return graph;
}
*/

// random maze generator with forest disjoint set
template <typename T>
ForestsDisjointSet<T> randomMazeForest(int rows, int columns)
{
    ForestsDisjointSet<T> ds(rows * columns);
    randomMaze(ds, rows, columns);
    return ds;
}

// random maze generator with linked list disjoint set
template <typename T>
ListDisjointSet<T> randomMazeLists(int rows, int columns)
{
    ListDisjointSet<T> ds(rows * columns);
    randomMaze(ds, rows, columns);
    return ds;
}
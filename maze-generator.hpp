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
    std::vector<Edge<T>> edges;
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
        // generate adjacent cell in the direction
        int adjacent = cell;
        /*
        // generate random direction
        int direction = rnd(gen) % 4;
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
        */
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

// random maze generator with forest disjoint set
template <typename T>
Graph<T> randomMazeForest(int rows, int columns)
{
    ForestsDisjointSet<T> ds(rows * columns);
    return randomMaze(ds, rows, columns);
}

// random maze generator with linked list disjoint set
template <typename T>
Graph<T> randomMazeLists(int rows, int columns)
{
    ListDisjointSet<T> ds(rows * columns);
    return randomMaze(ds, rows, columns);
}
#include <vector>
#include <random>
#include "disjoint-set.hpp"
#include "maze.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

// random maze generator with disjoint set with implied maze
template<typename T>
void randomMaze(DisjointSet<T> &ds, int rows, int columns) {
    int n = rows * columns;
    int start = 0;
    int end = n - 1;

    // random number generator
    std::uniform_int_distribution<> rnd(start, end);

    while (!ds.same(start, end)) {
        // generate random cell
        int cell = rnd(gen);

        // available neighbors
        int availableNeighbors[4];
        int availableNeighborsCount = 0;
        // check left
        if (cell % columns != 0 && !ds.same(cell - 1, cell))
            availableNeighbors[availableNeighborsCount++] = cell - 1;
        // check right
        if (cell % columns != columns - 1 && !ds.same(cell, cell + 1))
            availableNeighbors[availableNeighborsCount++] = cell + 1;
        // check up
        if (cell >= columns && !ds.same(cell - columns, cell))
            availableNeighbors[availableNeighborsCount++] = cell - columns;
        // check down
        if (cell < n - columns && !ds.same(cell, cell + columns))
            availableNeighbors[availableNeighborsCount++] = cell + columns;

        if (availableNeighborsCount == 0)
            continue;
        // generate random neighbor
        int neighbor = availableNeighbors[rnd(gen) % availableNeighborsCount];

        // remove wall between cell and adjacent by uniting the sets
        ds.unite(cell, neighbor);
    }
}

// random maze generator with disjoint set using maze class
template<typename T>
void randomMaze(Maze<T> &maze, DisjointSet<T> &ds) {
    int columns = maze.getColumns();
    int n = maze.getColumns() * maze.getRows();
    int start = 0;
    int end = n - 1;

    // random number generator
    std::uniform_int_distribution<> rnd(start, end);

    while (!ds.same(start, end)) {
        // generate random cell
        int cell = rnd(gen);

        // available neighbors
        int availableNeighbors[4];
        int availableNeighborsCount = 0;
        // check left
        if (cell % columns != 0 && !ds.same(cell - 1, cell))
            availableNeighbors[availableNeighborsCount++] = cell - 1;
        // check right
        if (cell % columns != columns - 1 && !ds.same(cell, cell + 1))
            availableNeighbors[availableNeighborsCount++] = cell + 1;
        // check up
        if (cell >= columns && !ds.same(cell - columns, cell))
            availableNeighbors[availableNeighborsCount++] = cell - columns;
        // check down
        if (cell < n - columns && !ds.same(cell, cell + columns))
            availableNeighbors[availableNeighborsCount++] = cell + columns;

        if (availableNeighborsCount == 0)
            continue;
        // generate random neighbor
        int neighbor = availableNeighbors[rnd(gen) % availableNeighborsCount];

        // remove wall between cell and adjacent
        if (!ds.same(cell, neighbor)) {
            ds.unite(cell, neighbor);
            maze.removeWall(cell, neighbor);
        }

    }
}


// random maze generator with forest disjoint set using maze class
template<typename T>
Maze<T> randomMazeForest(int rows, int columns) {
    ForestsDisjointSet<T> ds(rows * columns);
    //randomMaze(ds, rows, columns);
    Maze<T> maze(rows, columns);
    randomMaze(maze, ds);
    return maze;
}

// random maze generator with forest disjoint set
template<typename T>
ForestsDisjointSet<T> randomMazeForestSet(int rows, int columns) {
    ForestsDisjointSet<T> ds(rows * columns);
    randomMaze(ds, rows, columns);
    return ds;
}

// random maze generator with linked list disjoint set using maze class
template<typename T>
Maze<T> randomMazeList(int rows, int columns) {
    ListDisjointSet<T> ds(rows * columns);
    //randomMaze(ds, rows, columns);
    Maze<T> maze(rows, columns);
    randomMaze(maze, ds);
    return maze;
}

// random maze generator with linked list disjoint set
template<typename T>
ListDisjointSet<T> randomMazeListSet(int rows, int columns) {
    ListDisjointSet<T> ds(rows * columns);
    randomMaze(ds, rows, columns);
    return ds;
}
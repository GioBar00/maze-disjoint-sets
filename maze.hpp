#include <vector>
#include <list>

/*
 * Template class for Maze
 */
template<typename T>
class Maze {
    // list of cells
    std::vector<T> cells;

    /* list of walls as:
     * forall x, y: x, y are cells and x < y,
     * walls[x] contains y implies that there is a wall between x and y.
     */
    std::vector<std::list<T> > walls;
    int rows;
    int columns;

public:
    int getRows() { return rows; }

    int getColumns() { return columns; }

    Maze(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
        int n = rows * columns;
        cells.resize(n);
        walls.resize(n);
        for (int i = 0; i < n; i++) {
            cells[i] = i;
            // check right exists
            if (i % columns != columns - 1)
                walls[i].push_back(i + 1);
            // check down exists
            if (i < n - columns)
                walls[i].push_back(i + columns);
        }
    }

    // removes a wall from the maze
    void removeWall(T cell1, T cell2) {
        int c1, c2;
        if (cell1 < cell2) {
            c1 = cell1;
            c2 = cell2;
        } else {
            c1 = cell2;
            c2 = cell1;
        }
        walls[c1].remove(c2);
    }

    // return if a wall exists between two cells
    bool hasWall(T cell1, T cell2) {
        // cycle through the list of walls
        for (auto it = walls[cell1].begin(); it != walls[cell1].end(); it++)
            if (*it == cell2)
                return true;
        return false;
    }
};

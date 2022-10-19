#include <iostream>
#include <stack>
#include "maze-generator.hpp"

// depth-first search cell reachability
bool isReachable(Maze<int> &maze, int start, int goal) {
    int rows = maze.getRows();
    int columns = maze.getColumns();
    int n = rows * columns;
    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    stack.push(start);
    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        if (current == goal)
            return true;
        visited[current] = true;
        // search for unvisited neighbors
        int availableNeighbors[4];
        int availableNeighborsCount = 0;
        // check left
        if (current % columns != 0 && !visited[current - 1] &&
            !maze.hasWall(current - 1, current))
            availableNeighbors[availableNeighborsCount++] = current - 1;
        // check right
        if (current % columns != columns - 1 && !visited[current + 1] &&
            !maze.hasWall(current, current + 1))
            availableNeighbors[availableNeighborsCount++] = current + 1;
        // check up
        if (current >= columns && !visited[current - columns] &&
            !maze.hasWall(current - columns, current))
            availableNeighbors[availableNeighborsCount++] = current - columns;
        // check down
        if (current < columns * (rows - 1) && !visited[current + columns] &&
            !maze.hasWall(current, current + columns))
            availableNeighbors[availableNeighborsCount++] = current + columns;
        // push neighbors to stack
        for (int i = 0; i < availableNeighborsCount; i++)
            stack.push(availableNeighbors[i]);

    }
    return false;
}

void printRow(Maze<int> &maze, int row) {
    int columns = maze.getColumns();
    // print left border
    std::cout << "|";
    // print cells
    for (int j = 0; j < columns - 1; j++) {
        // print cell
        std::cout << "   ";
        // print right border
        if (maze.hasWall(row * columns + j, row * columns + j + 1))
            std::cout << "|";
        else
            std::cout << " ";
    }
    // print last cell
    std::cout << "   |" << std::endl;
}

// maze printer
void printMaze(Maze<int> &maze) {
    int rows = maze.getRows();
    int columns = maze.getColumns();
    // print top border
    for (int i = 0; i < columns; i++)
        std::cout << "+---";
    std::cout << "+" << std::endl;
    // print rows
    for (int i = 0; i < rows - 1; i++) {
        printRow(maze, i);
        // print bottom border
        for (int j = 0; j < columns; j++) {
            // print bottom border
            if (maze.hasWall(i * columns + j, i * columns + j + columns))
                std::cout << "+---";
            else
                std::cout << "+   ";
        }
        std::cout << "+" << std::endl;
    }
    // print last row
    printRow(maze, rows - 1);
    // print bottom border
    for (int i = 0; i < columns; i++)
        std::cout << "+---";
    std::cout << "+" << std::endl;
}

int main() {
    int rows, columns;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
    Maze<int> maze = randomMazeForest<int>(rows, columns);
    std::cout << "Is the end reachable? ";
    std::cout << isReachable(maze, 0, rows * columns - 1) << std::endl;
    printMaze(maze);
    return 0;
}

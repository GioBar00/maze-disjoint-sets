#include <iostream>
#include <stack>
#include "maze-generator.hpp"

// depth-first search node reacheability
bool isReachable(Graph<int> graph, int start, int end)
{
    std::stack<int> stack;
    std::vector<bool> visited(graph.n, false);
    stack.push(start);
    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();
        if (current == end)
            return true;
        visited[current] = true;
        // seach for unvisited neighbors in the edges list
        for (auto edge : graph.edges)
        {
            if (edge.from == current && !visited[edge.to])
                stack.push(edge.to);
            if (edge.to == current && !visited[edge.from])
                stack.push(edge.from);
        }
    }
    return false;
}

// ASCII maze printer
void printMaze(Graph<int> graph, int rows, int columns)
{
    // print top border
    std::cout << "*";
    for (int i = 0; i < columns; i++)
        std::cout << "**";
    std::cout << std::endl;
    // print maze
    for (int i = 0; i < rows; i++)
    {
        std::cout << "*";
        for (int j = 0; j < columns - 1; j++)
        {
            int current = i * columns + j;
            int right = i * columns + j + 1;
            bool found = false;
            for (auto edge : graph.edges)
            {
                if (edge.from == current && edge.to == right)
                {
                    std::cout << "  ";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << " *";
        }
        std::cout << " *" << std::endl;
        // print bottom border of the row
        std::cout << "*";
        for (int j = 0; j < columns; j++)
        {
            int current = i * columns + j;
            int bottom = (i + 1) * columns + j;
            bool found = false;
            for (auto edge : graph.edges)
            {
                if (edge.from == current && edge.to == bottom)
                {
                    std::cout << " *";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "**";
        }
        std::cout << std::endl;
    }
    // print bottom border
    std::cout << "*";
    for (int i = 0; i < columns; i++)
        std::cout << "**";
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    ListDisjointSet<int> ds(50);
    ds.unite(0, 1);
    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.find(3);
    int rows, columns;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;
    //Graph<int> graph = randomMazeForest<int>(rows, columns);
    std::cout << "Is the end reachable?" << std::endl;
    //std::cout << isReachable(graph, 0, rows * columns - 1) << std::endl;
    //printMaze(graph, columns, rows);
    return 0;
}

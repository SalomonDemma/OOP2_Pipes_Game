// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<iostream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "EnumAndConst.h"

using namespace std;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
public:
    Graph(int num = 0);  // Constructor

    void setNumOfVertices(int num);
    // function to add an edge to graph
    void addEdge(int v, int w);
    void clearNeighbors();
    // prints BFS traversal from a given source s
    std::vector<int> BFS(int source);
    void setPathComplete(bool complete);
    bool isPathComplete()const;
	Textures getPipe(int x, int y);
    void generatePath(int size); //function that create a path from source to target
    void clearMaze();
    bool visited(int x, int y) const;
    std::vector<sf::Vector2i> getPath() const;
   

private:
  
    int m_numOfVertices;    // No. of vertices
    bool m_pathComplete;
    // Pointer to an array containing adjacency lists
    std::vector<std::list<int>> m_adj;
    std::vector<sf::Vector2i> m_maze;

};



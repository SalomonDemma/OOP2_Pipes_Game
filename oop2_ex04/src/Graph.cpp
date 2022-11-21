#include "Graph.h"
#include <array>
Graph::Graph(int num)
{
    setNumOfVertices(num);
    setPathComplete(false);
}

void Graph::setNumOfVertices(int num)
{
    if (m_adj.size() > 0)
        clearNeighbors();

    this->m_numOfVertices = num;
    m_adj.resize(num);
}

void Graph::addEdge(int v, int w)
{
    m_adj[v].push_back(w); // Add w to v’s list.
}

void Graph::clearNeighbors()
{
    for (auto& vertex : m_adj)
        vertex.clear();
}

std::vector<int> Graph::BFS(int source)
{
    // Mark all the vertices as not visited
    std::vector<bool> visited;
    visited.resize(m_numOfVertices);
    for (int i = 0; i < m_numOfVertices; i++)
        visited[i] = false;
    
    // Build path for BFS
    std::vector<int> path;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[source] = true;
    queue.push_back(source);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator it;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        source = queue.front();
        path.push_back(source);
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (it = m_adj[source].begin(); it != m_adj[source].end(); ++it)
        {
            if (!visited[*it])
            {
                visited[*it] = true;
                queue.push_back(*it);
            }
        }
    }
    return path;
}

void Graph::setPathComplete(bool complete)
{
    m_pathComplete = complete;
}

bool Graph::isPathComplete() const
{
    return m_pathComplete;
}

Textures Graph::getPipe(int x, int y)
{

    for (decltype(m_maze.size()) vertex = 0; vertex < m_maze.size(); vertex++)
        if (m_maze[vertex].x == x && m_maze[vertex].y == y)
        {
            if (vertex == 0)						return Textures::t_Faucet;
            else if (vertex == m_maze.size() - 1)	return Textures::t_Sink;

            else if (m_maze[vertex - 1].x == m_maze[vertex + 1].x ||
                m_maze[vertex - 1].y == m_maze[vertex + 1].y)
                return Textures::t_Pipe1;

            else if ((m_maze[vertex - 1].x == m_maze[vertex + 1].x - 1) &&
                ((m_maze[vertex - 1].y == m_maze[vertex + 1].y + 1) ||
                    (m_maze[vertex - 1].y == m_maze[vertex + 1].y - 1))
                ||//another option
                ((m_maze[vertex - 1].x == m_maze[vertex + 1].x + 1) &&
                    ((m_maze[vertex - 1].y == m_maze[vertex + 1].y + 1) ||
                        (m_maze[vertex - 1].y == m_maze[vertex + 1].y - 1))))
                return Textures::t_Pipe2;

            else if ((m_maze[vertex - 1].y == m_maze[vertex + 1].y - 1) &&
                ((m_maze[vertex - 1].x == m_maze[vertex + 1].x - 1) ||
                    (m_maze[vertex - 1].x == m_maze[vertex + 1].x + 1))
                ||//another option
                ((m_maze[vertex - 1].y == m_maze[vertex + 1].y + 1) &&
                    ((m_maze[vertex - 1].x == m_maze[vertex + 1].x - 1) ||
                        (m_maze[vertex - 1].x == m_maze[vertex + 1].x + 1))))
                return Textures::t_Pipe3;

            else
                return Textures::t_Pipe4;

        }
    return Textures::t_EmptySpace;
}

bool Graph::visited(int x, int y) const
{
    for (auto vertex : m_maze)
        if (vertex.x == x && vertex.y == y)
        {
            return true;
        }
    return false;
}

std::vector<sf::Vector2i> Graph::getPath() const
{
    return m_maze;
}

void Graph::generatePath(int size)
{
    auto numOfSteps = size + size; 	  // number of steps for path
    auto xVal = rand() % size;		 //	randomize location for sink
    auto yVal = rand() % size;
    m_maze.push_back(sf::Vector2i(xVal, yVal));
    auto index = 0;
    std::array<bool, 4> deadEnd{ true,true,true,true };

    int counter = 0;
    while (index < numOfSteps)
    {
        switch (rand() % 4)
        {
        case 0:
            if (xVal > 0 && !visited(xVal - 1, yVal))
            {
                xVal--;
                m_maze.push_back(sf::Vector2i(xVal, yVal));
                index++;
                deadEnd[0] = true;
            }
            else deadEnd[0] = false;
            break;

        case 1:
            if (yVal < size - 1 && !visited(xVal, yVal + 1))
            {
                yVal++;
                m_maze.push_back(sf::Vector2i(xVal, yVal));
                index++;
                deadEnd[1] = true;
            }
            else deadEnd[1] = false;
            break;

        case 2:
            if (xVal < size - 1 && !visited(xVal + 1, yVal))
            {
                xVal++;
                m_maze.push_back(sf::Vector2i(xVal, yVal));
                index++;
                deadEnd[2] = true;
            }
            else deadEnd[2] = false;
            break;

        case 3:
            if (yVal > 0 && !visited(xVal, yVal - 1))
            {
                yVal--;
                m_maze.push_back(sf::Vector2i(xVal, yVal));
                index++;
                deadEnd[3] = true;
            }
            else deadEnd[3] = false;
            break;
        }
        
        for (int i = 0; i < deadEnd.size(); i++)
            if (deadEnd[i] == true)
                counter = 0;
            else
                counter++;

        if (counter == 4)
            numOfSteps--;
    }
}

void Graph::clearMaze()
{
    m_maze.clear();
}


#include "Board.h"
#include "Resources.h"
#include "Pipe1Dir.h"
#include "Pipe2Dir.h"
#include "Pipe3Dir.h"
#include "Pipe4Dir.h"
#include "Faucet.h"
#include "Sink.h"
#include <time.h>


Board::Board(const sf::Texture& tBackround) : m_source(0), m_target(0), m_size(0), m_level(0), m_taps(-1)
{
	m_background.setTexture(tBackround);
	m_textTitle.setFont(Resources::instance().getfont());
	m_textTaps.setFont(Resources::instance().getfont());
	addTaps();
	m_textTitle.setColor(sf::Color::Black);
	m_textTaps.setColor(sf::Color::Black);
	m_textTitle.setPosition(120, 0);
	m_textTaps.setPosition(750, 150);
	m_textTitle.setStyle(sf::Text::Bold);
	m_textTaps.setStyle(sf::Text::Bold);
	m_textTitle.setOutlineThickness(2);
	m_textTaps.setOutlineThickness(2);
	m_textTitle.setOutlineColor(sf::Color::Green);
	m_textTaps.setOutlineColor(sf::Color::Green);
	m_textTitle.setCharacterSize(100);
	m_textTaps.setCharacterSize(60);
}

void Board::tileRotate(sf::Vector2f pos, const sf::Event& mouseEvent)
{

	for (auto& vecTiles : m_boardGame)
		for (auto& tile : vecTiles)
			if (tile->checkContains(pos))
			{
				if (tile->getVertexNum() == m_target)
					return;
				tile->rotate(mouseEvent);
				m_graph.clearNeighbors();
				addTaps();
				return;
			}
}

void Board::updateConnections()
{
	m_graph.clearNeighbors();
	for (decltype(m_boardGame.size()) i = 0; i < m_boardGame.size(); i++)
		for (decltype(m_boardGame.size()) j = 0; j < m_boardGame[i].size(); j++)
		{
			if ((m_boardGame[i][j]->getDirection(Tile::Direction::Up) && i > 0) &&
				m_boardGame[i - 1][j]->getDirection(Tile::Direction::Down))
				m_graph.addEdge(m_boardGame[i][j]->getVertexNum(),
					m_boardGame[i - 1][j]->getVertexNum());

			if ((m_boardGame[i][j]->getDirection(Tile::Direction::Right)
				&& j < m_boardGame[i].size() - 1)
				&& m_boardGame[i][j + 1]->getDirection(Tile::Direction::Left))
				m_graph.addEdge(m_boardGame[i][j]->getVertexNum(),
					m_boardGame[i][j + 1]->getVertexNum());

			if ((m_boardGame[i][j]->getDirection(Tile::Direction::Down)
				&& i < m_boardGame.size() - 1)
				&& m_boardGame[i + 1][j]->getDirection(Tile::Direction::Up))
				m_graph.addEdge(m_boardGame[i][j]->getVertexNum(),
					m_boardGame[i + 1][j]->getVertexNum());

			if ((m_boardGame[i][j]->getDirection(Tile::Direction::Left) && j > 0) &&
				m_boardGame[i][j - 1]->getDirection(Tile::Direction::Right))
				m_graph.addEdge(m_boardGame[i][j]->getVertexNum(),
					m_boardGame[i][j - 1]->getVertexNum());
		}
}

void Board::runBfs()
{
	auto path = m_graph.BFS(m_source);

	for (decltype(m_boardGame.size()) i = 0; i < m_boardGame.size(); i++)
		for (decltype(m_boardGame.size()) j = 0; j < m_boardGame[i].size(); j++)
		{
			m_boardGame[i][j]->updateTile(false);
			for (auto index : path)
				if (m_boardGame[i][j]->getVertexNum() == index)
					fillFromSource((int)i,(int)j);
		}

}

void Board::fillFromSource(int i, int j)
{
	m_boardGame[i][j]->updateTile(true);
	if (m_boardGame[i][j]->getVertexNum() == m_target)
		m_graph.setPathComplete(true);
}

bool Board::levelCompleted() const
{
	return m_graph.isPathComplete();
}

std::string Board::getLevelNumStr() const
{
	return to_string(m_level+1);
}

void Board::shuffleTiles()
{
	for (decltype(m_boardGame.size()) i = 0; i < m_boardGame.size(); i++)
		for (decltype(m_boardGame.size()) j = 0; j < m_boardGame.size(); j++)
			if (m_boardGame[i][j]->getVertexNum() == m_target)
				setSinkPosition();
			else m_boardGame[i][j]->shuffleTile();
}

void Board::shuffleBoard()
{
	do { // check if the level is solved, if solved shuffle again 
		shuffleTiles();
		m_graph.setPathComplete(false);
		runBfs();
	} while (levelCompleted());
}

void Board::drawBoard(sf::RenderWindow& window)const
{
	window.draw(m_background);
	window.draw(m_textTitle);
	window.draw(m_textTaps);
	for (auto& vecTiles : m_boardGame)
		for (auto& tile : vecTiles)
			tile->draw(window);
}

void Board::updateTextLevel()
{
	m_level++;
	m_textTitle.setString("Pipes Puzzle Level " + to_string(m_level) + "\n\n");
}

void Board::addTaps()
{
	m_taps++;
	m_textTaps.setString("Taps " + to_string(m_taps));
}

Textures Board::randPipe()
{
	auto pipe = 0;
	if (m_size > 4) pipe = rand() % 4;
	else pipe = rand() % 3;

	switch (pipe)
	{
	case 0: return t_Pipe1;
	case 1: return t_Pipe2;
	case 2: return t_Pipe3;
	default: break;
	}
	return t_Pipe4;
}
void Board::setSinkPosition()
{
	auto temp = m_graph.getPath();
	auto sinkPos = temp[temp.size()-1];
	auto neighborPos = temp[temp.size() - 2];

	if (sinkPos.x == neighborPos.x)
	{
		auto diff = neighborPos.y - sinkPos.y;
		if (diff == -1)
		{
			m_boardGame[sinkPos.x][sinkPos.y]->setRotation(180);
			m_boardGame[sinkPos.x][sinkPos.y]->setCurrDirection(false, false, false, true);
		}
			
		else return;
	}
	else if (sinkPos.y == neighborPos.y)
	{
		auto diff = neighborPos.x - sinkPos.x;
		if (diff == -1)
		{
			m_boardGame[sinkPos.x][sinkPos.y]->setRotation(-90);
			m_boardGame[sinkPos.x][sinkPos.y]->setCurrDirection(true, false, false, false);
		}

		else 
		{
			m_boardGame[sinkPos.x][sinkPos.y]->setRotation(90);
			m_boardGame[sinkPos.x][sinkPos.y]->setCurrDirection(false, false, true, false);
		}
			
	} 
}
void Board::generatePuzzle(int size)
{
	m_graph.generatePath(size);
}

void Board::buildLevel()
{
	m_size = (rand() % 3) + 3; // rand a board size
	generatePuzzle(m_size);
	m_graph.setNumOfVertices(m_size * m_size);
	m_boardGame.resize(m_size);
	Textures pipeType;
	auto vertexCounter = 0;
	for (decltype(m_boardGame.size()) i = 0; i < m_boardGame.size(); i++)
		for (decltype(m_boardGame.size()) j = 0; j < m_boardGame.size(); j++)
		{
			if (m_graph.visited((int)i,(int)j))		pipeType = m_graph.getPipe((int)i,(int)j);
			else					pipeType = randPipe();

			switch (pipeType)
			{
			case t_Faucet:
				m_boardGame[i].push_back(std::make_unique<Faucet>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter));
				m_source = vertexCounter;										break;
			case t_Sink:
				m_boardGame[i].push_back(std::make_unique<Sink>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter));
				m_target = vertexCounter;										break;
			case t_Pipe1:
				m_boardGame[i].push_back(std::make_unique<Pipe1Dir>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter));	break;
			case t_Pipe2:
				m_boardGame[i].push_back(std::make_unique<Pipe2Dir>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter)); break;
			case t_Pipe3:
				m_boardGame[i].push_back(std::make_unique<Pipe3Dir>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter));	break;
			case t_Pipe4:
				m_boardGame[i].push_back(std::make_unique<Pipe4Dir>
					(i * TILE_SIZE + 200, j * TILE_SIZE + 200, vertexCounter)); break;
			}
			vertexCounter++;
			
		}
	shuffleBoard();
	updateTextLevel();
	m_graph.clearMaze();
}

void Board::resetBoard()
{
	m_graph.setPathComplete(false);
	for (auto& vecTiles : m_boardGame)
		vecTiles.clear();
	m_boardGame.clear();
	m_taps = -1;
	addTaps();
}

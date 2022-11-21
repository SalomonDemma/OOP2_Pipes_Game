#pragma once
#include <vector>
#include "Graph.h"
#include "Tile.h"

class Board {

public:
	Board(const sf::Texture& tBackround);
	void drawBoard(sf::RenderWindow& window)const;
	void tileRotate(sf::Vector2f pos, const sf::Event& mouseEvent);
	void updateConnections();
	void runBfs();
	bool levelCompleted() const;
	std::string getLevelNumStr() const;
	void buildLevel();
	void resetBoard();
	

private:
	void updateTextLevel();
	void addTaps();
	void generatePuzzle(int size);
	void fillFromSource(int i, int j);
	void shuffleTiles();
	void shuffleBoard();
	Textures randPipe();
	void setSinkPosition();

	int		m_source, m_target, m_size;
	int		m_level, m_taps;
	using BoardPieces = std::vector<std::vector<std::unique_ptr <Tile>>>;
	Graph		m_graph;
	BoardPieces m_boardGame;
	sf::Text	m_textTitle, m_textTaps;
	sf::Sprite  m_background;
};
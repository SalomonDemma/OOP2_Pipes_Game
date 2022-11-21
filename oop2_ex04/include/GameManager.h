#pragma once
#include "Board.h"
#include "Menu.h"

class GameManager {

public:
	GameManager();
	void run();



private:
	void runLevels();
	void handleEvents();
	void updateMenu();

	Menu				m_puzzleMenu;
	Board				m_board;
	sf::RenderWindow	m_window;

};
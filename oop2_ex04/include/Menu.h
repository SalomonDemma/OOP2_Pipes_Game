#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Resources.h"

class Menu
{
public:
	Menu(const sf::Texture& tBackround);
	void setMenuText(const std::string& newtext);
	void runMenu(sf::RenderWindow& window);
	
private:
	enum Button { Start, Exit, None }; // enum for button 

	void drawMenu(sf::RenderWindow& window) const;
	Button buttonPressed(sf::Vector2f pos)	const; 

	sf::Sprite  m_startButton;
	sf::Sprite  m_exitButtons;

	sf::Sprite	m_backround;
	sf::Text	m_text;
};
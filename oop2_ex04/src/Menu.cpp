#include "Menu.h"

Menu::Menu(const sf::Texture& backround)
{
	m_backround.setTexture(backround);
	setMenuText("Menu text");
	m_text.setFont(Resources::instance().getfont());
	m_text.setStyle(sf::Text::Bold);
	m_text.setColor(sf::Color::Black);
	m_text.setOutlineThickness(2);
	m_text.setOutlineColor(sf::Color::Green);
	m_text.setCharacterSize(150);

	m_startButton.setTexture(Resources::instance().getStartButton());
	m_exitButtons.setTexture(Resources::instance().getExitButton());

	m_startButton.setPosition({ 100, 500 });
	m_exitButtons.setPosition({ 600, 500 });
}

void Menu::setMenuText(const std::string& text)
{
	m_text.setString(text + "\n\n");
	m_text.setPosition(180, 60);
}

void Menu::drawMenu(sf::RenderWindow& window) const
{
	window.draw(m_backround);
	window.draw(m_text);
	window.draw(m_startButton);
	window.draw(m_exitButtons);
}

void Menu::runMenu(sf::RenderWindow& window)
{
	for (auto event = sf::Event{}; window.waitEvent(event);)
	{
		window.clear();
		drawMenu(window);
		window.display();

		switch (event.type)
		{
		case sf::Event::Closed: window.close(); break;
		case sf::Event::MouseButtonReleased:
			auto m_MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			auto button = buttonPressed(m_MousePos);
			switch (button)
			{
			case Menu::Start:				   return;
			case Menu::Exit: window.close();   return;
			case Menu::None:                   break;
			default:                           break;
			}
			break;
		}
	}
}

Menu::Button Menu::buttonPressed(sf::Vector2f pos) const // return which button was pressed
{
	if (m_startButton.getGlobalBounds().contains(pos))
		return Menu::Button::Start; // if pressed start button

	else if (m_exitButtons.getGlobalBounds().contains(pos))
		return Menu::Button::Exit; // if pressed exit button

	return Menu::Button::None;	   // non button was pressed
}

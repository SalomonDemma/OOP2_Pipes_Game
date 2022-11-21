#include "GameManager.h"
#include "Resources.h"
#include <iostream>

GameManager::GameManager(): m_puzzleMenu(Resources::instance().getMenuBackground()),
                            m_board(Resources::instance().getBoardBackground())
{
    m_puzzleMenu.setMenuText("Welcome to\nPipe Puzzle!\n\n");
}

void GameManager::run()
{
    srand(time(0));
    m_window.create(sf::VideoMode(1000, 750), "Pipe Puzzle Game");

    while (m_window.isOpen())
    {
        m_puzzleMenu.runMenu(m_window);
        m_board.resetBoard();
        m_board.buildLevel();
        m_board.updateConnections();
        runLevels();
    }
}

void GameManager::runLevels()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        m_board.drawBoard(m_window);
        m_window.display();
        if (m_board.levelCompleted())
        {
            updateMenu();
            return;
        }
        handleEvents();
        m_board.runBfs();
    }
}

void GameManager::handleEvents()
{
    if (auto event = sf::Event{}; m_window.waitEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed: m_window.close(); break;
        case sf::Event::MouseButtonReleased:
            auto mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
            if ((event.key.code == sf::Mouse::Left) || 
                (event.key.code == sf::Mouse::Right))
            {
                m_board.tileRotate(mousePos, event);
                m_board.updateConnections();
            }
        }
}

void GameManager::updateMenu()
{
    m_puzzleMenu.setMenuText("Pipe Puzzle!\n\tLevel " + m_board.getLevelNumStr());
}



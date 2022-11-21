#include "Tile.h"
#include "EnumAndConst.h"
#include <array>
#include <iostream>

Tile::Tile() :m_angle(0), m_vertexNum(0), m_isFull(false)
{
	m_originDirection = { {Up, false}, {Right, false}, {Down, false}, {Left, false} };
	m_currDirection = { {Up, false}, {Right, false}, {Down, false}, {Left, false} };
}

void Tile::setTexture(const sf::Texture& newTexture)
{
	m_sTile.setTexture(newTexture);
	m_sTile.setOrigin({ m_sTile.getGlobalBounds().width / 2,
					   m_sTile.getGlobalBounds().height / 2 });

}

void Tile::setTilePosition(float i, float j)
{
	m_sTile.setPosition(j, i);
}

void Tile::setTilePosition(sf::Vector2f pos)
{
	m_sTile.setPosition(pos);
}

void Tile::setVertexNum(int num)
{
	m_vertexNum = num;
}

void Tile::setOriginDirection(bool up, bool right, bool down, bool left)
{
	m_originDirection[Up] = up;
	m_originDirection[Down] = down;
	m_originDirection[Left] = left;
	m_originDirection[Right] = right;
	setCurrDirection(up, right, down, left);
}

void Tile::setCurrDirection(bool up, bool right, bool down, bool left)
{
	m_currDirection[Up] = up;
	m_currDirection[Down] = down;
	m_currDirection[Left] = left;
	m_currDirection[Right] = right;
}

bool Tile::getDirection(Direction dir)
{
	return m_currDirection[dir];
}

bool Tile::getOriginDirection(Direction dir)
{
	return m_originDirection[dir];
}

int Tile::getVertexNum() const
{
	return m_vertexNum;
}

void Tile::rotate(const sf::Event& mouseEvent)  //check the current direction of sprite, and then rotate to next 90 deg angle
{

	switch (mouseEvent.key.code)
	{
	case sf::Mouse::Left:
	{
		m_angle -= 90;
		setCurrDirection(m_currDirection[Right], m_currDirection[Down], m_currDirection[Left], m_currDirection[Up]);
		break;
	}
	case sf::Mouse::Right:
	{
		m_angle += 90;
		setCurrDirection(m_currDirection[Left], m_currDirection[Up], m_currDirection[Right], m_currDirection[Down]);
		break;
	}
	default:
		break;
	}

	m_sTile.setRotation(m_angle);
}

void Tile::draw(sf::RenderWindow& window) const
{
	window.draw(m_sTile);
}

bool Tile::checkContains(const sf::Vector2f pos) const
{
	return m_sTile.getGlobalBounds().contains(pos);
}

void Tile::setIsFull(bool full)
{
	m_isFull = full;
}

bool Tile::getIsFull(bool full) const
{
	return m_isFull;
}

void Tile::shuffleTile()
{
	auto rot = (rand() % 3) - 1;
	m_sTile.rotate(rot * 90);

	switch (rot)
	{
	case -1:
	{
		m_angle -= 90;
		setCurrDirection(m_currDirection[Right], m_currDirection[Down], m_currDirection[Left], m_currDirection[Up]);
		break;
	}
	case 1:
	{
		m_angle += 90;
		setCurrDirection(m_currDirection[Left], m_currDirection[Up], m_currDirection[Right], m_currDirection[Down]);
		break;
	}
	default:
		break;
	}
}

void Tile::setRotation(int deg)
{
	m_sTile.rotate(deg);
}

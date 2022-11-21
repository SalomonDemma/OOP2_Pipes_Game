#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"


class Tile {

public:

	Tile();
	virtual ~Tile() = default;

	enum Direction { Up, Down, Left, Right };

    void rotate(const sf::Event& mouseEvent);
	void setTexture(const sf::Texture &newTexture);
	void setTilePosition(float i, float j);
	void setTilePosition(sf::Vector2f pos);
	void setVertexNum(int num);
	void setOriginDirection(bool up, bool right, bool down, bool left);
	void setCurrDirection(bool up, bool right, bool down, bool left);
	bool getDirection(Direction dir);
	bool getOriginDirection(Direction dir);
	int getVertexNum() const;
	void draw(sf::RenderWindow &window) const;

	bool checkContains(const sf::Vector2f pos) const;
	void setIsFull(bool full);
	bool getIsFull(bool full)const;

	virtual void updateTile(bool full) = 0;
	void shuffleTile();
	void setRotation(int deg);


private:
	
	sf::Sprite m_sTile;
	float m_angle;
	std::map< Direction, bool> m_currDirection;
	std::map< Direction, bool> m_originDirection;
	int m_vertexNum;
	bool m_isFull;
};
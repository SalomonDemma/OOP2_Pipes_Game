#pragma once
#include "Tile.h"

class Pipe4Dir : public Tile
{
public:
	Pipe4Dir(float row, float col, int vertex);
	virtual void updateTile(bool full) override;
private:

};
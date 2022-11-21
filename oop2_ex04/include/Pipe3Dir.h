#pragma once
#include "Tile.h"

class Pipe3Dir : public Tile
{
public:
	Pipe3Dir(float row, float col, int vertex);
	virtual void updateTile(bool full) override;
private:

};
#pragma once
#include "Tile.h"

class Pipe1Dir : public Tile
{
public:
	Pipe1Dir(float row, float col, int vertex);
	virtual void updateTile(bool full) override;
private:


};
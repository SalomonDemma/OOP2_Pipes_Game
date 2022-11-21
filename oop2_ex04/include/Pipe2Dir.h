#pragma once
#include "Tile.h"

class Pipe2Dir : public Tile
{
public:
	Pipe2Dir(float row, float col, int vertex);
	virtual void updateTile(bool full) override;
private:


};
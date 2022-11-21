#pragma once
#include "Tile.h"

class Sink : public Tile 
{
public:
	Sink(int row, int col, int vertex);
	virtual void updateTile(bool full) override;
private:


};
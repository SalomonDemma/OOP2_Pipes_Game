#pragma once

#include "Tile.h"

class Faucet : public Tile
{
public:
	Faucet(int row, int col, int vertex);
	virtual void updateTile(bool full) override;
private:



};
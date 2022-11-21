#include "Faucet.h"

Faucet::Faucet(int row, int col, int vertex)
{
	setTexture(Resources::instance().getFaucet());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(false, true, false, false);
}

void Faucet::updateTile(bool full)
{
	setIsFull(true);
}

#include "Sink.h"

Sink::Sink(int row, int col, int vertex)
{
	setTexture(Resources::instance().getSink());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(false, true, false, false);
}

void Sink::updateTile(bool full)
{
	setIsFull(full);
}

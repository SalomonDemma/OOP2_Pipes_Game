#include "Pipe1Dir.h"

Pipe1Dir::Pipe1Dir(float row, float col, int vertex)
{
	setTexture(Resources::instance().getPipe1());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(false, true, false, true);
}

void Pipe1Dir::updateTile(bool full)
{
	if (full)
	{
		setIsFull(full);
		setTexture(Resources::instance().getFullPipe1());
	}
	else 
		setTexture(Resources::instance().getPipe1());
}




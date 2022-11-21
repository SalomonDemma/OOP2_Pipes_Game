#include "Pipe4Dir.h"


Pipe4Dir::Pipe4Dir(float row, float col, int vertex)
{
	setTexture(Resources::instance().getPipe4());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(true, true, true, true);
}

void Pipe4Dir::updateTile(bool full)
{
	if (full)
	{
		setIsFull(full);
		setTexture(Resources::instance().getFullPipe4());
	}
	else
		setTexture(Resources::instance().getPipe4());
}

#include "Pipe2Dir.h"


Pipe2Dir::Pipe2Dir(float row, float col, int vertex)
{
	setTexture(Resources::instance().getPipe2());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(true, false, false, true);
}

void Pipe2Dir::updateTile(bool full)
{
	if (full)
	{
		setIsFull(full);
		setTexture(Resources::instance().getFullPipe2());
	}
	else
		setTexture(Resources::instance().getPipe2());
}

#include "Pipe3Dir.h"


Pipe3Dir::Pipe3Dir(float row, float col, int vertex)
{
	setTexture(Resources::instance().getPipe3());
	setTilePosition(row, col);
	setVertexNum(vertex);
	setOriginDirection(true, true, false, true);
}

void Pipe3Dir::updateTile(bool full)
{
	if (full)
	{
		setIsFull(full);
		setTexture(Resources::instance().getFullPipe3());
	}
	else
		setTexture(Resources::instance().getPipe3());
}

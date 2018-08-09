
#include <algorithm>
#include <assert.h>

#include "Hand.h"
#include "Tile.h"

namespace mahjong
{
	void Hand::sort()
	{
		std::sort(m_inHandTiles.begin(), m_inHandTiles.end(), [](const Tile& lTile, const Tile& rTile) { return lTile.getData() > rTile.getData(); });
	}

	void Hand::putTileInHand(const Tile& newTile) 
	{
		m_inHandTiles.push_back(newTile);
	}

	Tile Hand::getTile(int index)
	{
		return m_inHandTiles[index];
	}
}
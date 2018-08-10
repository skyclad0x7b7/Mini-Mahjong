
#include <algorithm>
#include <assert.h>

#include "Hand.h"
#include "Tile.h"

namespace mahjong
{
	void Hand::sort()
	{
		std::sort(m_inHandTiles.begin(), m_inHandTiles.end());
	}

	void Hand::putTile(const Tile newTile)
	{
		m_inHandTiles.push_back(newTile);
	}

	Tile Hand::getTile(int index)
	{
		assert(0 <= index && index < m_inHandTiles.size());
		return m_inHandTiles[index];
	}
}
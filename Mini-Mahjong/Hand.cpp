
#include <algorithm>
#include <assert.h>

#include "Hand.h"
#include "Tile.h"
#include "Mentsu.h"

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

	Tile Hand::getTile(size_t index) const
	{
		assert(0 <= index && index < m_inHandTiles.size());
		return m_inHandTiles[index];
	}

	size_t Hand::getNumOfTiles() const
	{
		return m_inHandTiles.size();
	}

	Tile Hand::pickTile(TileMountain* pTileMountain)
	{
		Tile ret = pTileMountain->pickTile();
		putTile(ret);
		return ret;
	}

}
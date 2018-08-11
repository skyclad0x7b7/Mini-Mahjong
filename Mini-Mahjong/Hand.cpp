
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

	Tile Hand::discardTile(const size_t index)
	{
		assert(0 <= index && index < m_inHandTiles.size());
		Tile ret = m_inHandTiles[index];
		m_inHandTiles.erase(std::begin(m_inHandTiles) + index);
		return ret;
	}

	bool Hand::canChi(const Tile & newTile) const
	{
		bool result = false;
		TileType newTileType = newTile.getTileType();
		if (newTileType == TileType::Special)
			return false;


		// Get tile in hand if tiletype's same
		std::vector<Tile> tileList;
		for (int i = 0; i < m_inHandTiles.size(); i++)
		{
			if (m_inHandTiles[i].getTileType() == newTileType)
				tileList.push_back(m_inHandTiles[i]);
		}

		// 1. Left
		if (newTile.getTileNumber() <= 7 &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() + 1); }) != std::end(tileList) &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() + 2); }) != std::end(tileList))
			result = true;

		// 2. Center
		if (2 <= newTile.getTileNumber() && newTile.getTileNumber() <= 8 &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() - 1); }) != std::end(tileList) &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() + 1); }) != std::end(tileList))
			result = true;

		// 3. Right
		if (3 <= newTile.getTileNumber() &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() - 1); }) != std::end(tileList) &&
			std::find_if(std::begin(tileList), std::end(tileList), [&](const Tile& tile) { return tile.getTileNumber() == (newTile.getTileNumber() - 2); }) != std::end(tileList))
			result = true;

		return result;
	}

	bool Hand::canPong(const Tile& newTile) const
	{
		bool result = false;

		// Get count of same tiles in hand 
		int count = 0;
		for (int i = 0; i < m_inHandTiles.size(); i++)
		{
			if (m_inHandTiles[i].getData() == newTile.getData())
				count++;
		}

		if (count == 2) // if count == 3, it can Kang instead of Pong
			result = true;

		return result;
	}

	bool Hand::canKang(const Tile& newTile) const
	{
		bool result = false;

		// Get count of same tiles in hand 
		int count = 0;
		for (int i = 0; i < m_inHandTiles.size(); i++)
		{
			if (m_inHandTiles[i].getData() == newTile.getData())
				count++;
		}

		if (count == 3) // if count == 3, it can Kang instead of Pong
			result = true;

		return result;
	}
}
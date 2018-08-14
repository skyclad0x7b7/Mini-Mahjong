
#include <algorithm>
#include <assert.h>
#include <set>

#include "Hand.h"
#include "Tile.h"
#include "Mentsu.h"

namespace mahjong
{
	void Hand::reset()
	{
		m_inHandTiles.clear();
		m_openedMentsu.clear();
		m_discardedTiles.clear();
		m_agariTiles.clear();
		m_isClaimed = false;
	}

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

	// Should check with Player::canClaim() after this function
	const Tile Hand::discardTileBefore(const size_t index)
	{
		assert(0 <= index && index < m_inHandTiles.size());
		const Tile ret = m_inHandTiles[index];
		m_inHandTiles.erase(std::begin(m_inHandTiles) + index);
		return ret;
	}

	// Should check with Player::canClaim() before this function
	void Hand::discardTileAfter(const Tile newTile)
	{
		m_discardedTiles.push_back(newTile);
	}

	bool Hand::canChi(const Tile & newTile) const
	{
		bool result = false;
		TileType newTileType = newTile.getTileType();
		if (newTileType == TileType::Special)
			return false;


		// Get tile in hand if tiletype's same
		std::vector<Tile> tileList;
		for (size_t i = 0; i < m_inHandTiles.size(); i++)
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
		for (size_t i = 0; i < m_inHandTiles.size(); i++)
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
		for (size_t i = 0; i < m_inHandTiles.size(); i++)
		{
			if (m_inHandTiles[i].getData() == newTile.getData())
				count++;
		}

		if (count == 3) // if count == 3, it can Kang instead of Pong
			result = true;

		return result;
	}

	bool Hand::isTenpai()
	{
		m_agariTiles.clear();

		// Normal Tenpai Check

		if (!m_isClaimed)
		{
			Tile tempTile;
			std::vector<Tile> uniqueTiles = m_inHandTiles;
			std::set<Tile> s(uniqueTiles.begin(), uniqueTiles.end());
			uniqueTiles.assign(s.begin(), s.end());

			// Chitoitsu
			int headCount = 0;
			for (auto it : uniqueTiles)
			{
				int tileCount = std::count(std::begin(m_inHandTiles), std::end(m_inHandTiles), it);
				if (tileCount == 2)
					headCount++;
				else if (tileCount == 1)
					tempTile = it;
				else // count over 2, can't be Chitoitsu
					break;
			}
			if (headCount == 6)
			{
				m_agariTiles.push_back(tempTile);
				return true;
			}

			// Kokushi musou
			int yaochuCount = std::count_if(std::begin(uniqueTiles), std::end(uniqueTiles), [](const Tile& tile) { return tile.isYaochuTile(); });
			if (yaochuCount == 13) // Kokushi musou 13-way wait
			{
				m_agariTiles = uniqueTiles;
				return true;
			}
			else if(yaochuCount == 12)
			{
				// Kokushi musou 1-way wait
				for (auto it : Tiles::yaochuTiles)
					if (std::find(std::begin(uniqueTiles), std::end(uniqueTiles), it) == std::end(uniqueTiles))
						m_agariTiles.push_back(it);
				assert(m_agariTiles.size() != 0);
				return true;
			}
		}

		return false;
	}

	const std::vector<Tile>& Hand::getInHandTiles() const
	{
		return m_inHandTiles;
	}

	const std::vector<Mentsu>& Hand::getOpendMentsu() const
	{
		return m_openedMentsu;
	}

	const std::vector<Tile>& Hand::getDiscardedTiles() const
	{
		return m_discardedTiles;
	}

	const std::vector<Tile>& Hand::getAgariTiles() const
	{
		return m_agariTiles;
	}
}
#include "Shanten.h"

#include <set>
#include <algorithm>
#include <assert.h>

namespace mahjong
{
	Shanten::Shanten() {};
	Shanten::Shanten(const Shanten& other) {};
	Shanten::~Shanten() {};

	void Shanten::reset()
	{
		m_tiles.clear();
		m_agariTiles.clear();
	}

	Shanten* Shanten::GetInstance()
	{
		static Shanten ins;
		return &ins;
	}

	int Shanten::calcShanten(const std::vector<Tile>& tiles, bool isClaimed, int numOfClaim)
	{
		int retShanten = -1;
		reset();
		
		m_tiles = tiles;

		if (!isClaimed)
		{
			int chitoitsuShanten = getChitoitsuShanten(m_tiles);
			int kokushiShanten = getKokushiMusouShanten(m_tiles);
			retShanten = chitoitsuShanten < kokushiShanten ? chitoitsuShanten : kokushiShanten;
		}

		assert(retShanten != -1);
		return retShanten;
	}

	int Shanten::getChitoitsuShanten(const std::vector<Tile>& tiles)
	{
		int retShanten = -1;
		Tile tempTile;

		std::vector<Tile> uniqueTiles = tiles;
		std::set<Tile> s(uniqueTiles.begin(), uniqueTiles.end());
		uniqueTiles.assign(s.begin(), s.end());


		// Chitoitsu
		int headCount = 0;
		for (auto it : uniqueTiles)
		{
			int tileCount = std::count(std::begin(tiles), std::end(tiles), it);
			if (tileCount == 2)
				headCount++;
			else if (tileCount == 1)
				tempTile = it;
			else // count over 2, can't be Chitoitsu
				break;
		}
		if (headCount == 6)
		{
			// Chitoitsu Tenpai
			m_agariTiles.push_back(tempTile);
			retShanten = 0;
		}
		else
		{
			retShanten = 6 - headCount;
		}

		return retShanten;
	}

	int Shanten::getKokushiMusouShanten(const std::vector<Tile>& tiles)
	{
		int retShanten = -1;
		Tile tempTile;

		std::vector<Tile> uniqueTiles = tiles;
		std::set<Tile> s(uniqueTiles.begin(), uniqueTiles.end());
		uniqueTiles.assign(s.begin(), s.end());

		// Kokushi musou
		int yaochuCount = std::count_if(std::begin(uniqueTiles), std::end(uniqueTiles), [](const Tile& tile) { return tile.isYaochuTile(); });
		if (yaochuCount == 13) // Kokushi musou 13-way wait Tenpai
		{
			m_agariTiles = uniqueTiles;
			retShanten = 0;
		}
		else if (yaochuCount == 12)
		{
			// Kokushi musou 1-way wait Tenpai
			for (auto it : Tiles::yaochuTiles)
				if (std::find(std::begin(tiles), std::end(tiles), it) == std::end(tiles))
					m_agariTiles.push_back(it);
			assert(m_agariTiles.size() != 0);
			retShanten = 0;
		}
		else
		{
			retShanten = 12 - yaochuCount;
		}

		return retShanten;
	}

	std::vector<Tile> Shanten::getAgariTiles() const
	{
		return m_agariTiles;
	}
}
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
		m_toitsuNum = 0;
		m_shuntsuNum = 0;
		m_koutsuNum = 0;
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
			retShanten = (chitoitsuShanten < kokushiShanten) ? chitoitsuShanten : kokushiShanten;
			if (retShanten == 0)
				return retShanten;
		}

		int normalShanten = getNormalShanten(tiles);

		retShanten = (normalShanten < retShanten) ? normalShanten : retShanten;

		assert(retShanten != -1);
		return retShanten;
	}

	int Shanten::getChitoitsuShanten(const std::vector<Tile>& tiles)
	{
		int retShanten = 0;
		Tile tmpTile;

		std::vector<Tile> uniqueTiles = tiles;
		std::set<Tile> s(uniqueTiles.begin(), uniqueTiles.end());
		uniqueTiles.assign(s.begin(), s.end());


		// Chitoitsu
		int toitsuCount = 0;
		for (auto it : uniqueTiles)
		{
			int tileCount = std::count(std::begin(tiles), std::end(tiles), it);
			if (tileCount == 2)
				toitsuCount++;
			else if (tileCount == 1)
			{
				retShanten += 1;
				tmpTile = it;
			}
			else // count over 2
				retShanten += tileCount - 2;
		}

		if (toitsuCount == 6)
		{
			// Chitoitsu Tenpai
			m_agariTiles.push_back(tmpTile);
			retShanten = 0;
		}

		return retShanten / 2;
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

	int Shanten::getNormalShanten(std::vector<Tile> curTiles)
	{

		int ret = 7;
		
		int toitsuShanten = 7;
		int shuntsuShanten = 7;
		int koutsuShanten = 7;

		bool flag = false;
		unsigned int index = 0;

		std::vector<Tile> tmpTiles;
		while (index < curTiles.size())
		{
			if (index > 0 && curTiles[index] == curTiles[index - 1])
			{ // Skip same tiles
				index++;
				continue;
			}

			// 1. Find Toitsu (Head)
			if (m_toitsuNum == 0)
			{
				if (std::count(std::begin(curTiles), std::end(curTiles), curTiles[index]) >= 2)
				{
					flag = true;
					tmpTiles = curTiles;
					for (int i = 0; i < 2; i++)
						tmpTiles.erase(std::find(std::begin(tmpTiles), std::end(tmpTiles), curTiles[index]));
					
					m_toitsuNum++;
					toitsuShanten = getNormalShanten(tmpTiles);
					m_toitsuNum--;
				}

			}

			// 2. Find Koutsu
			if (std::count(std::begin(curTiles), std::end(curTiles), curTiles[index]) == 3)
			{
				flag = true;
				tmpTiles = curTiles;
				for (int i = 0; i < 3; i++)
					tmpTiles.erase(std::find(std::begin(tmpTiles), std::end(tmpTiles), curTiles[index]));

				m_koutsuNum++;
				koutsuShanten = getNormalShanten(tmpTiles);
				m_koutsuNum--;
			}

			// 3. Find Shuntsu : Sorted
			if (curTiles[index].getTileType() != TileType::Special &&
				std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTiles[index].getTileType() && t.getTileNumber() == curTiles[index].getTileNumber() + 1); }) != std::end(curTiles) &&
				std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTiles[index].getTileType() && t.getTileNumber() == curTiles[index].getTileNumber() + 2); }) != std::end(curTiles))
			{
				flag = true;
				tmpTiles = curTiles;
				tmpTiles.erase(std::find_if(std::begin(tmpTiles), std::end(tmpTiles), [&](const Tile& t) { return (t.getTileType() == curTiles[index].getTileType() && t.getTileNumber() == curTiles[index].getTileNumber() ); }));
				tmpTiles.erase(std::find_if(std::begin(tmpTiles), std::end(tmpTiles), [&](const Tile& t) { return (t.getTileType() == curTiles[index].getTileType() && t.getTileNumber() == curTiles[index].getTileNumber() + 1); }));
				tmpTiles.erase(std::find_if(std::begin(tmpTiles), std::end(tmpTiles), [&](const Tile& t) { return (t.getTileType() == curTiles[index].getTileType() && t.getTileNumber() == curTiles[index].getTileNumber() + 2); }));

				m_shuntsuNum++;
				shuntsuShanten = getNormalShanten(tmpTiles);
				m_shuntsuNum--;
			}

			index++;
		}

		// 4. Rest Tile Check
		tmpTiles.clear(); // Used to save agariTiles
		int restShanten = 7;
		if (flag == false) // false flag means there's no more tile which can be Mentsu
		{
			restShanten = (4 - m_koutsuNum - m_shuntsuNum) * 2 - 1;

			if (m_toitsuNum == 0)
				restShanten += 1;

			if (curTiles.size() == 1) // 4 Bodies, No Head
				tmpTiles.push_back(curTiles[0]);

			unsigned index = 0;
			while (index < curTiles.size())
			{
				Tile curTile = curTiles[index];
				// Check Shuntsu - one tile right
				if (curTile.getTileType() != TileType::Special &&
					curTile.getTileNumber() <= 7 &&
					std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber() + 1); }) != std::end(curTiles)
				)
				{
					if(curTile.getTileNumber() == 1)
						tmpTiles.push_back(Tile(curTile.getTileType(), curTile.getTileNumber() + 2, false));
					else
					{
						tmpTiles.push_back(Tile(curTile.getTileType(), curTile.getTileNumber() + 2, false));
						tmpTiles.push_back(Tile(curTile.getTileType(), curTile.getTileNumber() - 1, false));
					}

					curTiles.erase(std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber())); }));
					curTiles.erase(std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber() + 1)); }));
					restShanten--;
				}

				// Check Shuntsu - two tile right
				else if (curTile.getTileType() != TileType::Special &&
					curTile.getTileNumber() <= 7 &&
					std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber() + 2); }) != std::end(curTiles)
					)
				{
					tmpTiles.push_back(Tile(curTile.getTileType(), curTile.getTileNumber() + 1, false));
					curTiles.erase(std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber())); }));
					curTiles.erase(std::find_if(std::begin(curTiles), std::end(curTiles), [&](const Tile& t) { return (t.getTileType() == curTile.getTileType() && t.getTileNumber() == (curTile.getTileNumber() + 2)); }));
					restShanten--;
				}

				// Check Toitsu
				else if (std::count(std::begin(curTiles), std::end(curTiles), curTile) >= 2)
				{
					tmpTiles.push_back(Tile(curTile.getTileType(), curTile.getTileNumber(), false));
					for (int i = 0; i < 2; i++)
						curTiles.erase(std::find(std::begin(curTiles), std::end(curTiles), curTile));
					restShanten--;
				}
				else
				{
					index++;
					continue;
				}

				index = 0;
				continue;
			}
		}
		if (restShanten == 0)
		{
			for (auto it : tmpTiles)
			{
				if (std::find(std::begin(m_agariTiles), std::end(m_agariTiles), it) == std::end(m_agariTiles))
					m_agariTiles.push_back(it);
			}
			std::sort(m_agariTiles.begin(), m_agariTiles.end());
		}

		ret = (toitsuShanten < ret) ? toitsuShanten : ret;
		ret = (shuntsuShanten < ret) ? shuntsuShanten : ret;
		ret = (koutsuShanten < ret) ? koutsuShanten : ret;
		ret = (restShanten < ret) ? restShanten : ret;
		return ret;
	}

	std::vector<Tile> Shanten::getAgariTiles() const
	{
		return m_agariTiles;
	}
}
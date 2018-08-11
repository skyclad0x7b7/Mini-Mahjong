#include "TileMountain.h"
#include "Constant.h"

#include <assert.h>
#include <algorithm>
#include <random>

namespace mahjong
{
	std::vector<Tile> TileMountain::m_entireTile = std::vector<Tile>();
	
	TileMountain::TileMountain() {};
	TileMountain::TileMountain(const TileMountain& other) {};
	TileMountain::~TileMountain() {}
	

	TileMountain* TileMountain::GetInstance()
	{
		static TileMountain ins;
		return &ins;
	}

	void TileMountain::reset()
	{
		m_entireTile.clear();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				m_entireTile.push_back(Tile(TileType::Manzu, j, false));
				m_entireTile.push_back(Tile(TileType::Ponzu, j, false));
				m_entireTile.push_back(Tile(TileType::Souzu, j, false));
			}
			for (int j = 1; j < 8; j++)
			{
				m_entireTile.push_back(Tile(TileType::Special, j, false));
			}
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(std::begin(m_entireTile), std::end(m_entireTile), gen);
	}

	Tile TileMountain::pickTile()
	{
		assert(!m_entireTile.empty());
		Tile ret = m_entireTile[m_entireTile.size() - 1];
		m_entireTile.pop_back();
		return ret;
	}
}
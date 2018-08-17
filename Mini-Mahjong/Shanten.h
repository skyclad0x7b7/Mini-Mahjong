#ifndef Mini_Mahjong_Shanten_H__
#define Mini_Mahjong_Shanten_H__

#pragma once

#include "Tile.h"

#include <vector>

namespace mahjong
{
	/* [Singlton Class] Use Shanten::GetInstance() */
	class Shanten
	{
	public:
		static Shanten* GetInstance();
		void reset();

		int calcShanten(const std::vector<Tile>& tiles, bool isClaimed = false, int numOfClaim = 0);
		int getChitoitsuShanten(const std::vector<Tile>& tiles);
		int getKokushiMusouShanten(const std::vector<Tile>& tiles);
		int getNormalShanten(std::vector<Tile> curTiles);

		std::vector<Tile> getAgariTiles() const;
	private:
		Shanten();
		Shanten(const Shanten& other);
		~Shanten();

		unsigned int m_toitsuNum;
		unsigned int m_shuntsuNum;
		unsigned int m_koutsuNum;

		std::vector<Tile> m_tiles;
		std::vector<Tile> m_agariTiles;
	};
}

#endif
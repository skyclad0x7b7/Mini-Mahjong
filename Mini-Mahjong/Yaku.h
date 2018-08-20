#ifndef Mini_Mahjong_Yaku_H__
#define Mini_Mahjong_Yaku_H__

#pragma once

#include "TileMountain.h"
#include "Tile.h"

#include <vector>

namespace mahjong
{
	/* [Singleton Class] Use Yaku::GetInstance() */
	class Yaku
	{
	public:
		static Yaku* GetInstance();
		void reset();

		std::vector<CompletedTiles> testGetYaku(const std::vector<Tile>& curTiles, const std::vector<TileGroup>& openedMentsu, const Tile& agariTile, bool isClaimed, bool isTsumo);
		
	private:
		std::vector<CompletedTiles> getAllCompletedTiles(const std::vector<Tile>& curTiles, const Tile& agariTile, bool isTsumo);

		Yaku();
		Yaku(const Yaku& other);
		~Yaku();

		CompletedTiles m_completedTiles;
		unsigned int m_toitsuNum;
	};
}

#endif
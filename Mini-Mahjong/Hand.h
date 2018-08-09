#ifndef Mini_Mahjong_Hand_H__
#define Mini_Mahjong_Hand_H__

#pragma once

#include <vector>
#include "Tile.h"
#include "Mentsu.h"

namespace mahjong
{
	class Hand
	{
	public:
		void sort();
		void putTileInHand(const Tile& newTile);
		Tile getTile(int index);
		

	private:
		std::vector<Tile> m_inHandTiles;
		std::vector<Mentsu> m_openedMentsu;
		std::vector<Tile> m_discardedTiles;

		bool m_isClaimed;
	};
}

#endif
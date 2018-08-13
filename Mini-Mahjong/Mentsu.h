#ifndef Mini_Mahjong_Mentsu_H__
#define Mini_Mahjong_Mentsu_H__

#pragma once

#include <vector>

#include "Constant.h"
#include "Tile.h"

namespace mahjong
{
	class Mentsu
	{
	public:
		Mentsu(const std::vector<Tile>& newTiles, mahjong::MentsuType newMentsuType);

		mahjong::MentsuType getMentsuType() const;
		std::vector<Tile> getTilesList() const;
	private:
		mahjong::MentsuType m_mentsuType;
		std::vector<Tile> m_tiles;
	};
}

#endif
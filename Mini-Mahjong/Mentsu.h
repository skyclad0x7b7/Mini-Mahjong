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
		Mentsu(const Tile&, const Tile&, const Tile&); // Chi, Pong
		Mentsu(const Tile&, const Tile&, const Tile&, const Tile&); // Kang
	private:
		mahjong::MentsuType m_memtsuType;
		std::vector<Tile> m_tiles;
	};


}

#endif
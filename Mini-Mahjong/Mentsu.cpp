#include "Mentsu.h"

namespace mahjong
{
	Mentsu::Mentsu(const Tile& tile1, const Tile& tile2, const Tile& tile3)
	{
		// Koutsu
		if ((tile1.getData() == tile2.getData()) && (tile2.getData() == tile3.getData()))
			m_memtsuType = mahjong::MentsuType::Koutsu;
		// Shuntsu

		// Kangtsu
	}
}
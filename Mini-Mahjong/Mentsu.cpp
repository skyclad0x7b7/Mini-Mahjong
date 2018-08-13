#include "Mentsu.h"

namespace mahjong
{
	Mentsu::Mentsu(const std::vector<Tile>& newTiles, mahjong::MentsuType newMentsuType)
	{
		m_tiles      = newTiles;
		m_mentsuType = newMentsuType;
	}

	mahjong::MentsuType Mentsu::getMentsuType() const
	{
		return m_mentsuType;
	}

	std::vector<Tile> Mentsu::getTilesList() const
	{
		return m_tiles;
	}
}
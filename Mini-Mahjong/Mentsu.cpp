#include "Mentsu.h"

namespace mahjong
{
	Mentsu::Mentsu()
	{

	}

	Mentsu::Mentsu(const std::vector<Tile>& newTiles, MentsuType newMentsuType)
	{
		m_tiles      = newTiles;
		m_mentsuType = newMentsuType;
	}

	void Mentsu::putTile(const Tile& newTile)
	{
		m_tiles.push_back(newTile);
	}

	void Mentsu::setMentsuType(const MentsuType& newMentsuType)
	{
		m_mentsuType = newMentsuType;
	}

	MentsuType Mentsu::getMentsuType() const
	{
		return m_mentsuType;
	}

	std::vector<Tile> Mentsu::getTilesList() const
	{
		return m_tiles;
	}
}
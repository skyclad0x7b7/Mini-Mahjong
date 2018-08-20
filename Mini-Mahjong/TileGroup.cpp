#include "TileGroup.h"

namespace mahjong
{
	TileGroup::TileGroup()
	{

	}

	TileGroup::TileGroup(const std::vector<Tile>& newTiles, TileGroupType newTileGroupType)
	{
		m_tiles      = newTiles;
		m_tileGroupType = newTileGroupType;
	}

	void TileGroup::putTile(const Tile& newTile)
	{
		m_tiles.push_back(newTile);
	}

	void TileGroup::setTileGroupType(const TileGroupType& newTileGroupType)
	{
		m_tileGroupType = newTileGroupType;
	}

	TileGroupType TileGroup::getTileGroupType() const
	{
		return m_tileGroupType;
	}

	std::vector<Tile> TileGroup::getTilesList() const
	{
		return m_tiles;
	}
}
#ifndef Mini_Mahjong_TileGroup_H__
#define Mini_Mahjong_TileGroup_H__

#pragma once

#include <vector>

#include "Constant.h"
#include "Tile.h"

namespace mahjong
{
	class TileGroup
	{
	public:
		TileGroup();
		TileGroup(const std::vector<Tile>& newTiles, TileGroupType newTileGroupType);

		void reset();

		void putTile(const Tile& newTile);
		void setTileGroupType(const TileGroupType& newTileGroupType);
		TileGroupType getTileGroupType() const;
		std::vector<Tile> getTilesList() const;
	private:
		TileGroupType m_tileGroupType;
		std::vector<Tile> m_tiles;
	};
}

#endif
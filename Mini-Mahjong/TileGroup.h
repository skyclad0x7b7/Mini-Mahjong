#ifndef Mini_Mahjong_TileGroupType_H__
#define Mini_Mahjong_TileGroupType_H__

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
		TileGroup(const std::vector<Tile>& newTiles, mahjong::TileGroupType newTileGroupType);

		void putTile(const Tile& newTile);
		void setTileGroupType(const mahjong::TileGroupType& newTileGroupType);
		mahjong::TileGroupType getTileGroupType() const;
		std::vector<Tile> getTilesList() const;
	private:
		mahjong::TileGroupType m_tileGroupType;
		std::vector<Tile> m_tiles;
	};
}

#endif
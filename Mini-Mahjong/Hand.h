#ifndef Mini_Mahjong_Hand_H__
#define Mini_Mahjong_Hand_H__

#pragma once

#include <vector>

#include "Tile.h"
#include "TileGroup.h"
#include "TileMountain.h"

namespace mahjong
{
	class Hand
	{
	public:
		virtual void reset();

		void sort();
		
		void putTile(const Tile newTile);
		Tile getTile(size_t index) const;
		const std::vector<Tile>& getInHandTiles() const;
		const std::vector<TileGroup>& getOpendMentsu() const;
		const std::vector<Tile>& getDiscardedTiles() const;
		const std::vector<Tile>& getAgariTiles() const;
		const int getShanten() const;
		const bool isClaimed() const;

		const Tile discardTileBefore(const size_t index);
		void discardTileAfter(const Tile newTile);

		void doChi(const TileGroup&);
		void doPong(const Tile& tile);
		TileGroupType doKangBefore(const Tile& tile, bool isTsumo);
		void doKangAfter(const Tile& tile, TileGroupType);

		std::vector<TileGroup> getTileGroupCanChi(const Tile& newTile) const;

		virtual bool canChi(const Tile& newTile, bool isTsumo) const;
		virtual bool canPong(const Tile& newTile, bool isTsumo) const;
		virtual bool canKang(const Tile& newTile, bool isTsumo) const;
		virtual bool isTenpai();
	private:
		std::vector<Tile> m_inHandTiles;
		std::vector<TileGroup> m_openedMentsu;
		std::vector<Tile> m_discardedTiles;
		std::vector<Tile> m_agariTiles;
		bool m_isClaimed;

		int m_shanten;
	};
}

#endif
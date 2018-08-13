#ifndef Mini_Mahjong_Hand_H__
#define Mini_Mahjong_Hand_H__

#pragma once

#include <vector>

#include "Tile.h"
#include "Mentsu.h"
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
		const std::vector<Mentsu>& getOpendMentsu() const;
		const std::vector<Tile>& getDiscardedTiles() const;

		const Tile discardTileBefore(const size_t index);
		void discardTileAfter(const Tile newTile);

		virtual bool canChi(const Tile& newTile) const;
		virtual bool canPong(const Tile& newTile) const;
		virtual bool canKang(const Tile& newTile) const;

	private:
		std::vector<Tile> m_inHandTiles;
		std::vector<Mentsu> m_openedMentsu;
		std::vector<Tile> m_discardedTiles;
		bool m_isClaimed;
	};
}

#endif
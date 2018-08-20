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
		const std::vector<Tile>& getAgariTiles() const;
		const int getShanten() const;

		const Tile discardTileBefore(const size_t index);
		void discardTileAfter(const Tile newTile);

		//void doChi(const Tile& tile1, const Tile& tile2, const Tile& tile3);
		//void doPong(const Tile& tile);
		//Tile doKang(const Tile& tile);

		virtual bool canChi(const Tile& newTile) const;
		virtual bool canPong(const Tile& newTile) const;
		virtual bool canKang(const Tile& newTile) const;
		virtual bool isTenpai();
	private:
		std::vector<Tile> m_inHandTiles;
		std::vector<Mentsu> m_openedMentsu;
		std::vector<Tile> m_discardedTiles;
		std::vector<Tile> m_agariTiles;
		bool m_isClaimed;

		int m_shanten;
	};
}

#endif
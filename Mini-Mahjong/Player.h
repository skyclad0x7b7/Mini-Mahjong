#ifndef Mini_Mahjong_Player_H__
#define Mini_Mahjong_Player_H__

#pragma once

#include <string>

#include "Hand.h"
#include "Tile.h"
#include "TileMountain.h"

namespace mahjong
{
	class Player
	{
	public:
		Player(const std::string playerName) : m_playerName(playerName) {}
		virtual ~Player() {}

		void initialize(const int score, const Wind& wind);

		Tile pickTile(TileMountain* pTileMountain);

		const Tile discardTileBefore(const size_t index);
		void discardTileAfter(const Tile newTile);

		bool canClaim(const Tile& newTile, const Wind& wind) const;

	private:
		std::string m_playerName;
		Wind m_wind;

		int m_score;
		Hand m_hand;
	};

}

#endif
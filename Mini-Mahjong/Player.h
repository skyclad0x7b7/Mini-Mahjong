#ifndef Mini_Mahjong_Player_H__
#define Mini_Mahjong_Player_H__

#pragma once

#include <string>

#include "Hand.h"
#include "Tile.h"
#include "TileMountain.h"

namespace mahjong
{
	class Player : public Hand
	{
	public:
		Player(const std::string playerName) : m_playerName(playerName) {}
		virtual ~Player() {}

		void changeWind();
		void changeWind(const Wind& newWind);

		void initialize(const int score, const Wind& wind);

		Tile pickTile(TileMountain* pTileMountain);

		const mahjong::ClaimType canClaim(const Tile& newTile, const Wind& wind) const;
	private:
		std::string m_playerName;
		Wind m_wind;
		int m_score;
	};

}

#endif
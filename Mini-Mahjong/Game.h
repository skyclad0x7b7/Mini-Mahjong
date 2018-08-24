#ifndef Mini_Mahjong_Game_H__
#define Mini_Mahjong_Game_H__

#pragma once

#include "Player.h"
#include "TileMountain.h"

namespace mahjong
{
	class Game
	{
	public:
		Game(Player *p1);
		~Game();
		virtual void startGame();
	private:
		Game::Game();

		Player *m_player1;

		Wind m_roundWind;
	};
}


#endif
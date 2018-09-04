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
		Game(Player *p1, Player *p2, Player *p3, Player *p4);
		~Game();
		virtual void startGame();
	private:
		Game::Game();
		Player *m_players[4];
		Wind m_roundWind;
		
		unsigned int m_kangCount;
	
	};
}


#endif
#ifndef Mini_Mahjong_Game_H__
#define Mini_Mahjong_Game_H__

#pragma once

#include "Player.h"

namespace mahjong
{
	class Game
	{
	public:
		Game(Player *p1, Player *p2, Player *p3, Player *p4);

		virtual void startGame();
	private:
		Player m_player1;
		Player m_player2;
		Player m_player3;
		Player m_player4;
	};
}


#endif
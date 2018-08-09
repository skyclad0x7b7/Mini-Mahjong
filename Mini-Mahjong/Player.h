#ifndef Mini_Mahjong_Player_H__
#define Mini_Mahjong_Player_H__

#pragma once

#include <string>

namespace mahjong
{
	class Player
	{
	public:
		Player(const std::string playerName) : m_playerName(playerName) {}
		virtual ~Player() {}

	private:
		std::string m_playerName;
		int m_score;
	};

}

#endif
#ifndef Mini_Mahjong_Test_H__
#define Mini_Mahjong_Test_H__

#pragma once

#include "Tile.h"
#include "Player.h"

#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <assert.h>

namespace mahjong
{
	namespace Test
	{
		std::string tileToString(const mahjong::Tile& t);
		void testPrintPlayer(const mahjong::Player& p);
		void testCanClaim();
		void testIsTenpai();
		void testYaku();
	}
}

#endif
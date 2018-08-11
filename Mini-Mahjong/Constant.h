#ifndef Mini_Mahjong_Constant_H__
#define Mini_Mahjong_Constant_H__

#pragma once

#include <type_traits>

namespace mahjong
{
	/*
	* TileData : 0b0000XXXX
	*    - Suzi : (1~9) 1-base
	*    - Special : {East, South, West, North, Hyaku, Patsu, Chun} 1-base
	*/

	/*
	* TileType : 0bXX000000
	*/
	enum TileType
	{
		Manzu   = 0b00000000,
		Souzu   = 0b01000000,
		Ponzu   = 0b10000000,
		Special = 0b11000000
	};
	
	enum class MentsuType
	{
		Shuntsu,
		Koutsu,
		Kangtsu
	};

	enum class Wind 
	{
		East,
		South,
		West,
		North
	};

	Wind operator++(Wind& wind)
	{
		wind = static_cast<Wind>((static_cast<int>(wind) + 1) % 4);
		return wind;
	}

	Wind operator+(const Wind& wind, const int i)
	{
		Wind ret = static_cast<Wind>((static_cast<int>(wind) + i) % 4);
		return ret;
	}

	Wind operator-(const Wind& wind, const int i)
	{
		Wind ret = static_cast<Wind>((static_cast<int>(wind) - (i % 4) + 4) % 4);
		return ret;
	}
}

#endif
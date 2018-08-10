#include <iostream>
#include <bitset>

#include "Tile.h"
#include "Hand.h"


int main()
{
	mahjong::Hand hand;
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 8, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 7, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 6, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 5, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 4, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	hand.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	hand.sort();
	
	for (int i = 0; i <= 12; i++)
		std::cout << std::bitset<8>(hand.getTile(i).getData()) << std::endl;

	system("pause");
	return 0;
}
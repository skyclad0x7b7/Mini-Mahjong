#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "TileMountain.h"
#include "Tile.h"
#include "Hand.h"


void testPrint(const mahjong::Hand& h);

int main()
{
	mahjong::Hand hand[4];
	mahjong::TileMountain::GetInstance()->reset();


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			hand[i].pickTile(mahjong::TileMountain::GetInstance());
		}
		hand[i].sort();
		std::cout << "[*] Player " << i << " : ";
		testPrint(hand[i]);
	}
	system("pause");
	return 0;
}

void testPrint(const mahjong::Hand& h)
{
	size_t len = h.getNumOfTiles();
	for (unsigned int i = 0; i < len; i++)
	{
		std::string out = "";
		switch (h.getTile(i).getTileType())
		{
		case mahjong::TileType::Manzu:
			out = std::to_string(h.getTile(i).getTileNumber()) + "만";
			break;
		case mahjong::TileType::Ponzu:
			out = std::to_string(h.getTile(i).getTileNumber()) + "통";
			break;
		case mahjong::TileType::Souzu:
			out = std::to_string(h.getTile(i).getTileNumber()) + "삭";
			break;
		case mahjong::TileType::Special:
			switch (h.getTile(i).getTileNumber())
			{
			case 0b00000001:
				out = "동";
				break;
			case 0b00000010:
				out = "남";
				break;
			case 0b00000011:
				out = "서";
				break;
			case 0b00000100:
				out = "북";
				break;
			case 0b00000101:
				out = "백";
				break;
			case 0b00000110:
				out = "발";
				break;
			case 0b00000111:
				out = "중";
				break;
			default:
				std::cerr << "Unknown Special Character : " << std::bitset<8>(h.getTile(i).getData()) << std::endl;
				system("pause");
			}
			break;
		default:
			std::cerr << "Unknown Type : " << std::bitset<8>(h.getTile(i).getData()) << std::endl;
			system("pause");
		}
		std::cout << std::setw(4) << out;
	}
	std::cout << std::endl;
}
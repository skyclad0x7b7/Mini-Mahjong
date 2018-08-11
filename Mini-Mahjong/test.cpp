#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "TileMountain.h"
#include "Tile.h"
#include "Hand.h"


void testPrint(const mahjong::Hand& h);
void testCanChi();
void testCanPong();
void testCanKang();


int main()
{
	/*
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
	*/

	testCanChi();
	testCanPong();
	testCanKang();
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

void testCanChi()
{
	std::cout << " ====== << CanChi >> ====== " << std::endl;
	mahjong::Hand h;
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Souzu, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Souzu, 6, false));

	// Left Test
	if (h.canChi(mahjong::Tile(mahjong::TileType::Manzu, 1, false)))
	{
		std::cout << "[*] Left Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Left Test Not Passed" << std::endl;
	}

	// Center Test
	if (h.canChi(mahjong::Tile(mahjong::TileType::Ponzu, 4, false)))
	{
		std::cout << "[*] Center Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Center Test Not Passed" << std::endl;
	}

	// Right Test
	if (h.canChi(mahjong::Tile(mahjong::TileType::Souzu, 7, false)))
	{
		std::cout << "[*] Right Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Right Test Not Passed" << std::endl;
	}

	// Special Test
	if (h.canChi(mahjong::Tile(mahjong::TileType::Special, 1, false)) == false)
	{
		std::cout << "[*] Special Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Special Test Not Passed" << std::endl;
	}
}

void testCanPong()
{
	std::cout << " ====== << CanPong >> ====== " << std::endl;

	mahjong::Hand h;
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Souzu, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Souzu, 6, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	

	// Left Test
	if (h.canPong(mahjong::Tile(mahjong::TileType::Manzu, 2, false)))
	{
		std::cout << "[*] Test1 Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Test1 Not Passed" << std::endl;
	}

	// Center Test
	if (h.canPong(mahjong::Tile(mahjong::TileType::Ponzu, 3, false)))
	{
		std::cout << "[*] Test2 Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Test2 Not Passed" << std::endl;
	}

	// Right Test
	if (h.canPong(mahjong::Tile(mahjong::TileType::Souzu, 5, false)) == false)
	{
		std::cout << "[*] Test3 Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Test3 Not Passed" << std::endl;
	}

	// Special Test
	if (h.canPong(mahjong::Tile(mahjong::TileType::Special, 5, false)) == false)
	{
		std::cout << "[*] Special Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Special Test Not Passed" << std::endl;
	}
}

void testCanKang()
{
	std::cout << " ====== << CanKang >> ====== " << std::endl;

	mahjong::Hand h;
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Souzu, 6, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	h.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));


	// Left Test
	if (h.canKang(mahjong::Tile(mahjong::TileType::Manzu, 2, false)))
	{
		std::cout << "[*] Test1 Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Test1 Not Passed" << std::endl;
	}

	// Right Test
	if (h.canKang(mahjong::Tile(mahjong::TileType::Ponzu, 3, false)) == false)
	{
		std::cout << "[*] Test2 Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Test2 Not Passed" << std::endl;
	}

	// Special Test
	if (h.canKang(mahjong::Tile(mahjong::TileType::Special, 5, false)))
	{
		std::cout << "[*] Special Test Passed" << std::endl;
	}
	else
	{
		std::cout << "[*] Special Test Not Passed" << std::endl;
	}
}
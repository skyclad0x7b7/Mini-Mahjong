#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <assert.h>

#include "Player.h"
#include "TileMountain.h"
#include "Tile.h"
#include "Hand.h"
#include "Yaku.h"

std::string tileToString(const mahjong::Tile& t);
void testPrint(const mahjong::Player& p);
void testCanClaim();
void testIsTenpai();
void testYaku();

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
	testYaku();

	system("pause");
	return 0;
}

std::string tileToString(const mahjong::Tile& t)
{
	std::string out = "";
	switch (t.getTileType())
	{
	case mahjong::TileType::Manzu:
		out = std::to_string(t.getTileNumber()) + "Ø¿";
		break;
	case mahjong::TileType::Ponzu:
		out = std::to_string(t.getTileNumber()) + "÷Õ";
		break;
	case mahjong::TileType::Souzu:
		out = std::to_string(t.getTileNumber()) + "ßã";
		break;
	case mahjong::TileType::Special:
		switch (t.getTileNumber())
		{
		case 0b00000001:
			out = "ÔÔ";
			break;
		case 0b00000010:
			out = "Ñõ";
			break;
		case 0b00000011:
			out = "à¤";
			break;
		case 0b00000100:
			out = "ÝÁ";
			break;
		case 0b00000101:
			out = "ÛÜ";
			break;
		case 0b00000110:
			out = "Û¡";
			break;
		case 0b00000111:
			out = "ñé";
			break;
		default:
			std::cerr << "Unknown Special Character : " << std::bitset<8>(t.getData()) << std::endl;
			system("pause");
		}
		break;
	default:
		std::cerr << "Unknown Type : " << std::bitset<8>(t.getData()) << std::endl;
		system("pause");
	}
	return out;
}

void testPrint(const mahjong::Player& p)
{
	size_t len = p.getInHandTiles().size();
	for (unsigned int i = 0; i < len; i++)
	{
		std::string out = tileToString(p.getTile(i));
		std::cout << std::setw(4) << out;
	}
	std::cout << std::endl;
}

void testCanClaim()
{
	mahjong::Player player1("P1");
	
	player1.initialize(25000, mahjong::Wind::East);

	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 2, false));
	
	player1.sort();

	if (player1.canClaim(mahjong::Tile(mahjong::TileType::Manzu, 1, false), mahjong::Wind::North) & mahjong::ClaimType::Chi)
		std::cout << "[*] Test 1 Passed" << std::endl;

	if (player1.canClaim(mahjong::Tile(mahjong::TileType::Manzu, 4, false), mahjong::Wind::North) & mahjong::ClaimType::Chi)
		std::cout << "[*] Test 2 Passed" << std::endl;

	if (player1.canClaim(mahjong::Tile(mahjong::TileType::Manzu, 1, false), mahjong::Wind::West) == mahjong::ClaimType::None)
		std::cout << "[*] Test 3 Passed" << std::endl;

	if (player1.canClaim(mahjong::Tile(mahjong::TileType::Ponzu, 3, false), mahjong::Wind::West) & mahjong::ClaimType::Pong)
		std::cout << "[*] Test 4 Passed" << std::endl;

	if (player1.canClaim(mahjong::Tile(mahjong::TileType::Souzu, 2, false), mahjong::Wind::West) & mahjong::ClaimType::Kang)
		std::cout << "[*] Test 5 Passed" << std::endl;
	
}

void testIsTenpai()
{
	mahjong::Player player1("P1");
	player1.initialize(25000, mahjong::Wind::East);

	
	// Kokushi musou 13-way wait
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 7, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Kokushi musou 1-way wait
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 9, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 6, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Chitoitsu - Tenpai
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 7, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 7, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Chitoitsu - No Tenpai
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Tenpai (Head)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Tenpai (Body - Koutsu)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Tenpai (Body - Shuntsu - Right)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}
	
	// Tenpai (Body - Shuntsu - Left)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 8, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 9, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// Tenpai (Body - Shuntsu - Middle)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 7, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// No Tenpai
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 7, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false)); 
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}

	// No Tenpai
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 8, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Ponzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 6, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Souzu, 7, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	if (player1.isTenpai())
	{
		std::cout << "[*] Tenpai, Agari Tile : ";
		for (auto it : player1.getAgariTiles())
			std::cout << std::setw(4) << tileToString(it);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::clog << "[*] Shanten : " << player1.getShanten() << std::endl << std::endl;
	}
}

void testYaku()
{
	mahjong::Player player1("P1");
	player1.initialize(25000, mahjong::Wind::East);

	// Tenpai (Head)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 4, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 5, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	std::vector<mahjong::CompletedTiles> ret = mahjong::Yaku::GetInstance()->testGetYaku(player1.getInHandTiles(), player1.getOpendMentsu(), mahjong::Tile(mahjong::TileType::Special, 5, false), player1.isClaimed(), true);
	if (ret.size() > 0)
	{
		std::cout << "[*] Tsumo Success" << std::endl;
		for (auto it : ret) {
			std::cout << "    [*] Head : " << std::setw(4) << tileToString(it.head.getTilesList()[0]) << " " <<  std::setw(4) << tileToString(it.head.getTilesList()[1]) << std::endl;
			std::cout << "    [*] Body : ";
			for(auto bIt : it.body)
				for(auto tId : bIt.getTilesList())
					std::cout << std::setw(4) << tileToString(tId);
			std::cout << std::endl << std::endl;
		}
	}
	else
	{
		std::clog << "[*] Tsumo Failed" << std::endl;
	}

	// Tenpai (Body)
	player1.reset();
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Special, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 3, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 2, false));
	player1.putTile(mahjong::Tile(mahjong::TileType::Manzu, 1, false));
	player1.sort();
	std::cout << " < Tiles >" << std::endl;
	testPrint(player1);
	ret = mahjong::Yaku::GetInstance()->testGetYaku(player1.getInHandTiles(), player1.getOpendMentsu(), mahjong::Tile(mahjong::TileType::Special, 2, false), player1.isClaimed(), true);
	if (ret.size() > 0)
	{
		std::cout << "[*] Tsumo Success" << std::endl;
		for (auto it : ret) {
			std::cout << "    [*] Head : " << std::setw(4) << tileToString(it.head.getTilesList()[0]) << " " << std::setw(4) << tileToString(it.head.getTilesList()[1]) << std::endl;
			std::cout << "    [*] Body : ";
			for (auto bIt : it.body) {
				std::cout << " | ";
				for (auto tId : bIt.getTilesList())
					std::cout << std::setw(4) << tileToString(tId);
				
			}
			std::cout << std::endl << std::endl;
		}
	}
	else
	{
		std::clog << "[*] Tsumo Failed" << std::endl;
	}
}

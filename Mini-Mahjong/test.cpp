#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "Player.h"
#include "TileMountain.h"
#include "Tile.h"
#include "Hand.h"


void testPrint(const mahjong::Player& p);
void testCanClaim();

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
	testCanClaim();
	system("pause");
	return 0;
}

void testPrint(const mahjong::Player& p)
{
	size_t len = p.getInHandTiles().size();
	for (unsigned int i = 0; i < len; i++)
	{
		std::string out = "";
		switch (p.getTile(i).getTileType())
		{
		case mahjong::TileType::Manzu:
			out = std::to_string(p.getTile(i).getTileNumber()) + "Ø¿";
			break;
		case mahjong::TileType::Ponzu:
			out = std::to_string(p.getTile(i).getTileNumber()) + "÷Õ";
			break;
		case mahjong::TileType::Souzu:
			out = std::to_string(p.getTile(i).getTileNumber()) + "ßã";
			break;
		case mahjong::TileType::Special:
			switch (p.getTile(i).getTileNumber())
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
				std::cerr << "Unknown Special Character : " << std::bitset<8>(p.getTile(i).getData()) << std::endl;
				system("pause");
			}
			break;
		default:
			std::cerr << "Unknown Type : " << std::bitset<8>(p.getTile(i).getData()) << std::endl;
			system("pause");
		}
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
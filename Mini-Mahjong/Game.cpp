#include "Game.h"
#include "Test.h"
#include "Shanten.h"
#include "Yaku.h"

#include <iostream>

namespace mahjong
{
	void Game::startGame()
	{
		// Initialize
		mahjong::TileMountain::GetInstance()->reset();
		m_roundWind = Wind::East;

		m_player1.reset();
		m_player1.initialize(25000, mahjong::Wind::East);

		// Distribute Tiles
		for (int i = 0; i < 13; i++)
			m_player1.putTile(mahjong::TileMountain::GetInstance()->pickTile());
		
		while (mahjong::TileMountain::GetInstance()->getRestTilesCount() != 0)
		{
			// Print Current Tiles
			m_player1.sort();
			Test::testPrintPlayer(m_player1);

			// Pick tile
			Tile t = mahjong::TileMountain::GetInstance()->pickTile();
			std::cout << "    Picked Tile : " << std::setw(4) << Test::tileToString(t) << std::endl;
			

			if (m_player1.canClaim(t, m_roundWind))
			{
				if (m_player1.canChi(t))
					std::cout << "Can Chi" << std::endl;
				if (m_player1.canKang(t))
					std::cout << "Can Kang" << std::endl;
				else if (m_player1.canPong)
					std::cout << "Can Pong" << std::endl;
			}
			m_player1.putTile(t);
			
			// Discard Tile
			Test::testPrintPlayer(m_player1);
			std::cout << "[*] Pick a tile offset to discard (0-base) : " << std::endl;
			int count = 0;
			std::cin >> count;

			t = m_player1.discardTileBefore(count);
			// Should check other player's Claim on here
			m_player1.discardTileAfter(t);

			std::cout << "===============================================" << std::endl;
		}

	}
}
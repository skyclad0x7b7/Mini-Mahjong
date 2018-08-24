#include "Game.h"
#include "Test.h"
#include "Shanten.h"
#include "Yaku.h"

#include <iostream>

namespace mahjong
{
	Game::Game() {}

	Game::~Game() { delete m_player1; }

	Game::Game(Player *p1)
	{
		m_player1 = p1;
	}

	void Game::startGame()
	{
		// Initialize
		mahjong::TileMountain::GetInstance()->reset();
		m_roundWind = Wind::East;

		m_player1->reset();
		m_player1->initialize(25000, mahjong::Wind::East);

		// Distribute Tiles
		for (int i = 0; i < 13; i++)
			m_player1->putTile(mahjong::TileMountain::GetInstance()->pickTile());
		
		while (mahjong::TileMountain::GetInstance()->getRestTilesCount() != 0)
		{
			// Print Current Tiles
			m_player1->sort();
			Test::testPrintPlayer(*m_player1);

			// Pick tile
			Tile t = mahjong::TileMountain::GetInstance()->pickTile();
			std::cout << "    Picked Tile : " << std::setw(4) << Test::tileToString(t) << std::endl;

			// Agari Check
			if (std::find(std::begin(m_player1->getAgariTiles()), std::end(m_player1->getAgariTiles()), t) != std::end(m_player1->getAgariTiles()))
			{
				// Agari
				Yaku::GetInstance()->reset();
				std::cout << "[*] Tsumo" << std::endl;
				std::vector<CompletedTiles> ret = Yaku::GetInstance()->testGetYaku(m_player1->getInHandTiles(), m_player1->getOpendMentsu(), t, m_player1->isClaimed(), true);
				
				if (ret.size() > 0)
				{
					for (auto it : ret) {
						std::cout << "    [*] Head : " << std::setw(4) << Test::tileToString(it.head.getTilesList()[0]) << " " << std::setw(4) << Test::tileToString(it.head.getTilesList()[1]) << std::endl;
						std::cout << "    [*] Body : ";
						for (auto bIt : it.body)
							for (auto tId : bIt.getTilesList())
								std::cout << std::setw(4) << Test::tileToString(tId);
						std::cout << std::endl << std::endl;
					}
				}
				break;
			}

			if (m_player1->canKang(t))
				std::cout << "[*] Can Kang" << std::endl;

			m_player1->putTile(t);
			
			// Discard Tile
			Test::testPrintPlayer(*m_player1);
			int count = 0;
			while (true)
			{
				std::cout << "[*] Pick a tile offset to discard : ";
				std::cin >> count;
				if (0 <= count && count < m_player1->getInHandTiles().size())
					break;
				else
					std::cout << "[-] Please input an integer in range" << std::endl;
			}
			

			t = m_player1->discardTileBefore(count);
			// Should check other player's Claim on here
			if(m_player1->isTenpai())
				std::cout << "[*] Can Richi" << std::endl;
			else
				std::cout << "[*] Shanten : " << m_player1->getShanten() << std::endl;
			m_player1->discardTileAfter(t);

			std::cout << "===============================================" << std::endl;
		}

	}
}
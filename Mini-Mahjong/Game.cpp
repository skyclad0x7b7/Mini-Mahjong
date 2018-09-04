#include "Game.h"
#include "Test.h"
#include "Shanten.h"
#include "Yaku.h"

#include <iostream>

namespace mahjong
{
	Game::Game() {}

	Game::~Game() { 
		for (int i = 0; i < 4; i++)
			delete m_players[i];
	}

	Game::Game(Player *p1, Player *p2, Player *p3, Player *p4)
	{
		m_kangCount = 0;
		m_players[0] = p1;
		m_players[1] = p2;
		m_players[2] = p3;
		m_players[3] = p4;
	}

	void Game::startGame()
	{
		// Initialize
		mahjong::TileMountain::GetInstance()->reset();
		m_roundWind = Wind::East;

		for(int i = 0; i < 4; i++)
			m_players[i]->reset();
		m_players[0]->initialize(25000, mahjong::Wind::East);
		m_players[1]->initialize(25000, mahjong::Wind::North);
		m_players[2]->initialize(25000, mahjong::Wind::West);
		m_players[3]->initialize(25000, mahjong::Wind::South);

		// Distribute Tiles
		for(int i = 0; i < 4; i++)
			for (int j = 0; j < 13; j++)
				m_players[i]->putTile(mahjong::TileMountain::GetInstance()->pickTile());
		
		int curPlayer = 0;
		while (mahjong::TileMountain::GetInstance()->getRestTilesCount() != 0)
		{
			curPlayer = curPlayer % 4;
			m_players[curPlayer]->sort();
			std::cout << " ========== [ P" << curPlayer + 1 << " : " << m_players[curPlayer]->getPlayerName() << "(" << Test::windToString(m_players[curPlayer]->getWind()) << ") " << m_players[curPlayer]->getScore() << "p ] ==========" << std::endl;

			// Pick tile
			Tile t = mahjong::TileMountain::GetInstance()->pickTile();
			std::cout << "    Picked Tile : " << std::setw(4) << Test::tileToString(t) << std::endl;
			

			// Agari Check
			if (std::find(std::begin(m_players[curPlayer]->getAgariTiles()), std::end(m_players[curPlayer]->getAgariTiles()), t) != std::end(m_players[curPlayer]->getAgariTiles()))
			{
				// Agari
				Yaku::GetInstance()->reset();
				std::cout << "[*] Tsumo" << std::endl;
				std::vector<CompletedTiles> ret = Yaku::GetInstance()->testGetYaku(*m_players[curPlayer], t, true);
				
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

			// Kang Check
			Tile tmpKangTile = t;
			while (true)
			{
				if (m_players[curPlayer]->canKang(tmpKangTile, true)) {
					std::string select;
					std::cout << "[*] Do Kang? (y/n) : ";
					std::cin >> select;
					if (select == "y")
					{
						TileGroupType kangType = m_players[curPlayer]->doKangBefore(tmpKangTile, true);
						if (kangType == TileGroupType::Shouminkang)
						{
							// ChanKang Check
						}
						TileGroup kangGroup = m_players[curPlayer]->doKangAfter(tmpKangTile, kangType);

						std::cout << "[*] Kang : ";
						for (auto it : kangGroup.getTilesList())
							std::cout << std::setw(4) << it.toString();
						std::cout << std::endl;

						// Get Rinshan-Tile
						m_players[curPlayer]->sort();

						// Pick tile
						tmpKangTile = mahjong::TileMountain::GetInstance()->pickTile();
						std::cout << "    Picked Rinshan-Tile : " << std::setw(4) << Test::tileToString(tmpKangTile) << std::endl;
						// Agari Check
						if (std::find(std::begin(m_players[curPlayer]->getAgariTiles()), std::end(m_players[curPlayer]->getAgariTiles()), tmpKangTile) != std::end(m_players[curPlayer]->getAgariTiles()))
						{
							// Agari
							Yaku::GetInstance()->reset();
							std::cout << "[*] Rinshan-Tsumo" << std::endl;
							std::vector<CompletedTiles> ret = Yaku::GetInstance()->testGetYaku(*m_players[curPlayer], tmpKangTile, true);

							if (ret.size() > 0)
							{
								for (auto it : ret) 
								{
									std::cout << "    [*] Head : " << std::setw(4) << Test::tileToString(it.head.getTilesList()[0]) << " " << std::setw(4) << Test::tileToString(it.head.getTilesList()[1]) << std::endl;
									std::cout << "    [*] Body : ";
									for (auto bIt : it.body)
										for (auto tId : bIt.getTilesList())
											std::cout << std::setw(4) << Test::tileToString(tId);
									std::cout << std::endl << std::endl;
								}
								break;
							}
						}

						continue;

					}
					else
					{
						m_players[curPlayer]->putTile(tmpKangTile);
						break;
					}
				}
				else
				{
					m_players[curPlayer]->putTile(tmpKangTile);
					break;
				}
			}

			// Discard Tile
			Test::testPrintPlayer(*m_players[curPlayer]);
			int count = 0;
			while (true)
			{
				std::cout << "[*] Pick a tile offset to discard : ";
				std::cin >> count;
				if (0 <= count && count < m_players[curPlayer]->getInHandTiles().size())
					break;
				else
					std::cout << "[-] Please input an integer in range" << std::endl;
			}
			

			t = m_players[curPlayer]->discardTileBefore(count);
			// Should check other player's Claim on here
			if(m_players[curPlayer]->isTenpai())
				std::cout << "[*] Can Richi" << std::endl;
			else
				std::cout << "[*] Shanten : " << m_players[curPlayer]->getShanten() << std::endl;
			m_players[curPlayer]->discardTileAfter(t);

			std::cout << " ======================================= " << std::endl << std::endl;
			curPlayer++;
		}

	}
}
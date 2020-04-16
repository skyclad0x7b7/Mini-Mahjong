#include <Test/Test.h>

#include <Source/Tile.h>
#include <Source/Hand.h>
#include <Source/Player.h>
#include <Source/Utils.h>

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>

namespace Mini
{

    /*
    *  All tiles should be printed
    */
    void Test01()
    {
        puts(" ========== < Test 01 > ========== ");
        // Wind Tiles
        puts("[ Wind Tiles ]");
        printf(" %s %s %s %s\n\n", WindTile(WindType::East).ToString().c_str(), WindTile(WindType::South).ToString().c_str(), WindTile(WindType::West).ToString().c_str(), WindTile(WindType::North).ToString().c_str());

        // Dragon Tiles
        puts("[ Dragon Tiles ]");
        printf(" %s %s %s\n\n", DragonTile(DragonType::White).ToString().c_str(), DragonTile(DragonType::Green).ToString().c_str(), DragonTile(DragonType::Red).ToString().c_str());

        // Number Tiles
        puts("[ Number Tiles ]");
        printf(" %s %s %s %s %s %s %s %s %s\n", NumberTile(NumberType::Cracks, 1).ToString().c_str(), NumberTile(NumberType::Cracks, 2).ToString().c_str(), NumberTile(NumberType::Cracks, 3).ToString().c_str(), NumberTile(NumberType::Cracks, 4).ToString().c_str(), NumberTile(NumberType::Cracks, 5).ToString().c_str(), NumberTile(NumberType::Cracks, 6).ToString().c_str(), NumberTile(NumberType::Cracks, 7).ToString().c_str(), NumberTile(NumberType::Cracks, 8).ToString().c_str(), NumberTile(NumberType::Cracks, 9).ToString().c_str());
        printf(" %s %s %s %s %s %s %s %s %s\n\n", NumberTile(NumberType::Bamboo, 1).ToString().c_str(), NumberTile(NumberType::Bamboo, 2).ToString().c_str(), NumberTile(NumberType::Bamboo, 3).ToString().c_str(), NumberTile(NumberType::Bamboo, 4).ToString().c_str(), NumberTile(NumberType::Bamboo, 5).ToString().c_str(), NumberTile(NumberType::Bamboo, 6).ToString().c_str(), NumberTile(NumberType::Bamboo, 7).ToString().c_str(), NumberTile(NumberType::Bamboo, 8).ToString().c_str(), NumberTile(NumberType::Bamboo, 9).ToString().c_str());
        printf(" %s %s %s %s %s %s %s %s %s\n", NumberTile(NumberType::Dots, 1).ToString().c_str(), NumberTile(NumberType::Dots, 2).ToString().c_str(), NumberTile(NumberType::Dots, 3).ToString().c_str(), NumberTile(NumberType::Dots, 4).ToString().c_str(), NumberTile(NumberType::Dots, 5).ToString().c_str(), NumberTile(NumberType::Dots, 6).ToString().c_str(), NumberTile(NumberType::Dots, 7).ToString().c_str(), NumberTile(NumberType::Dots, 8).ToString().c_str(), NumberTile(NumberType::Dots, 9).ToString().c_str());
        puts(" ================================= ");
    }

    /*
    *  Make tile list used to play game, and take 13 pieces randomly.
    */
    void Test02()
    {
        puts(" ========== < Test 02 > ========== ");
        auto tileList = GetCompleteTileLists();
        std::random_device rd; 
        std::mt19937 g(rd());
        std::shuffle(tileList.begin(), tileList.end(), g);

        Hand hand(std::vector(tileList.begin(), tileList.begin() + 13));
        hand.Sort();
        for (int i = 0; i < 13; ++i)
        {
            printf(" %s", hand.GetReadOnlyTiles()[i].get().ToString().c_str());
        }
        printf("\n\n");

        for (const Tile& tile : tileList)
        {
            delete &tile;
        }
        puts(" ================================= ");
    }

    /*
    *  One player game. Player just drops a tile and takes new one.
    */
    void Test03()
    {
        std::vector<TileCRef> orgTileList = GetCompleteTileLists();
        std::vector<TileCRef> tileList = orgTileList;
        std::random_device rd; 
        std::mt19937 g(rd());
        std::shuffle(tileList.begin(), tileList.end(), g);

        Player player(std::vector(tileList.begin(), tileList.begin() + 13));
        tileList = std::vector(tileList.begin() + 13, tileList.end());

        while (tileList.size() != 0)
        {
            const Tile& newTile = tileList[tileList.size() - 1];
            tileList.pop_back();

            player.SortHand();
            const auto& handTiles = player.GetReadOnlyTiles();
            for (int i = 0; i < handTiles.size(); ++i)
            {
                printf("%s ", handTiles[i].get().ToString().c_str());
            }
            printf("   %s\n", newTile.ToString().c_str());
            
            int index = -1;
            while (index < 0 || index > handTiles.size())
            {
                printf(" Index of tile to drop: ");
                scanf("%d", &index);
            }

            if (index == handTiles.size())
            {
                // Tsumogiri
                player.AddToDroppedTile(newTile);
            }
            else
            {
                auto const& droppedTile = handTiles[index];
                player.DropTile(droppedTile);
                player.AddTile(newTile);
                player.AddToDroppedTile(droppedTile);
            }
            
            puts(" ----------------------------- ");
        }

        for (Tile const& tile : orgTileList)
        {
            delete &tile;
        }

        puts(" ================================= ");
    }

    /*
    *  Possibility Check : Chitoitsu & Kokushimusou (It's just test, so I don't free allocated memory)
    */
    void Test04()
    {
        /* Chitoitsu Test */
        {
            puts("[  Chitoitsu Test 01  ]");
            std::vector<TileCRef> chitoitsuTest01List = { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1),
                                                        *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Bamboo, 4),
                                                        *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8),
                                                        *new WindTile(WindType::West), *new WindTile(WindType::West), *new DragonTile(DragonType::Red),
                                                        *new DragonTile(DragonType::Red), };
            const Tile& pickedTile = *new NumberTile(NumberType::Cracks, 1);
            printf("[*] Tiles: ");
            for (const Tile& tile : chitoitsuTest01List)
            {
                printf("%s ", tile.ToString().c_str());
            }
            printf("    %s\n", pickedTile.ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckChitoitsuPossible({}, chitoitsuTest01List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }

        {
            puts("[  Chitoitsu Test 02  ]");
            std::vector<TileCRef> chitoitsuTest02List = { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1),
                                                        *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Bamboo, 4),
                                                        *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8),
                                                        *new WindTile(WindType::West), *new WindTile(WindType::West), *new DragonTile(DragonType::Red),
                                                        *new DragonTile(DragonType::Red), };
            const Tile& pickedTile = *new NumberTile(NumberType::Cracks, 3);
            printf("[*] Tiles: ");
            for (const Tile& tile : chitoitsuTest02List)
            {
                printf("%s ", tile.ToString().c_str());
            }
            printf("    %s\n", pickedTile.ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckChitoitsuPossible({}, chitoitsuTest02List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }

        {
            puts("[  Chitoitsu Test 03  ]");
            std::vector<TileCRef> chitoitsuTest03List = { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3),
                                                        *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Bamboo, 4),
                                                        *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8),
                                                        *new WindTile(WindType::West), *new WindTile(WindType::West), *new DragonTile(DragonType::Red),
                                                        *new DragonTile(DragonType::Red), };
            const Tile& pickedTile = *new NumberTile(NumberType::Cracks, 1);
            printf("[*] Tiles: ");
            for (const Tile& tile : chitoitsuTest03List)
            {
                printf("%s ", tile.ToString().c_str());
            }
            printf("    %s\n", pickedTile.ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckChitoitsuPossible({}, chitoitsuTest03List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }

        /* Kokushimusou Test */
        {
            puts("[  Kokushimusou Test 01  ]");
            std::vector<TileCRef> chitoitsuTest01List = { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 9), *new NumberTile(NumberType::Bamboo, 1),
                                                        *new NumberTile(NumberType::Bamboo, 9), *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 9),
                                                        *new WindTile(WindType::East), *new WindTile(WindType::South), *new WindTile(WindType::West),
                                                        *new WindTile(WindType::North), *new DragonTile(DragonType::White), *new DragonTile(DragonType::Green),
                                                        *new DragonTile(DragonType::Red), };
            const Tile& pickedTile = *new NumberTile(NumberType::Cracks, 1);
            printf("[*] Tiles: ");
            for (const Tile& tile : chitoitsuTest01List)
            {
                printf("%s ", tile.ToString().c_str());
            }
            printf("    %s\n", pickedTile.ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckKokushimusouPossible({}, chitoitsuTest01List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }

        {
            puts("[  Kokushimusou Test 02  ]");
            std::vector<TileCRef> chitoitsuTest02List = { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 9), *new NumberTile(NumberType::Bamboo, 1),
                                                        *new NumberTile(NumberType::Bamboo, 9), *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 9),
                                                        *new WindTile(WindType::East), *new WindTile(WindType::South), *new WindTile(WindType::West),
                                                        *new WindTile(WindType::North), *new DragonTile(DragonType::White), *new DragonTile(DragonType::Green),
                                                        *new DragonTile(DragonType::Red), };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 1);
            printf("[*] Tiles: ");
            for (auto& tile : chitoitsuTest02List)
            {
                printf("%s ", tile.get().ToString().c_str());
            }
            printf("    %s\n", pickedTile.get().ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckKokushimusouPossible({}, chitoitsuTest02List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }

        {
            puts("[  Kokushimusou Test 03  ]");
            std::vector<TileCRef> chitoitsuTest03List = { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Bamboo, 1),
                                                        *new NumberTile(NumberType::Bamboo, 9), *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 9),
                                                        *new WindTile(WindType::East), *new WindTile(WindType::South), *new WindTile(WindType::West),
                                                        *new WindTile(WindType::North), *new DragonTile(DragonType::White), *new DragonTile(DragonType::Green),
                                                        *new DragonTile(DragonType::Red), };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 9);
            printf("[*] Tiles: ");
            for (auto& tile : chitoitsuTest03List)
            {
                printf("%s ", tile.get().ToString().c_str());
            }
            printf("    %s\n", pickedTile.get().ToString().c_str());

            ReassembledTileGroup result;
            bool isPassed = CheckKokushimusouPossible({}, chitoitsuTest03List, pickedTile, result);
            printf("[*] Result: %s\n\n", isPassed ? "TRUE" : "FALSE");
        }
    }

    /*
    *  Yaku Test : Menzen, Yakuhai, Tanyao, Pinfu
    */
    void Test05()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            const Tile& pickedTile = *new NumberTile(NumberType::Dots, 5);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 5);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 6);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Koutsu, { *new WindTile(WindType::West), *new WindTile(WindType::West), *new WindTile(WindType::West) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 5);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;

            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
    }

    /*
    *  Yaku Test : ( Menzen, Yakuhai, Tanyao, Pinfu ), Ipeko, Ryanpeko, Ikkitsukan
    */
    void Test06()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL),
            new Ipeko("Ipeko", 1, 0, YakuType::N_PEKO),
            new Ryanpeko("Ryanpeko", 3, 1, YakuType::N_PEKO),
            new Ikkitsuukan("Ikkitsuukan", 2, 1, YakuType::GENERAL)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 8);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 5) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 5);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 6),
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 5);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 6), *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 7);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 05  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 7);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 06  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 4), *new NumberTile(NumberType::Cracks, 5), *new NumberTile(NumberType::Cracks, 6) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 7), *new NumberTile(NumberType::Cracks, 8), *new NumberTile(NumberType::Cracks, 9) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 7)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 7);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
        
        {
            puts("[  Yaku Test 07  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 5), *new NumberTile(NumberType::Bamboo, 6) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8), *new NumberTile(NumberType::Bamboo, 9) }),
                },
                {
                    *new NumberTile(NumberType::Bamboo, 1),
                    *new NumberTile(NumberType::Bamboo, 3)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Bamboo, 2);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
    }

    /*
    *  Yaku Test : ( Menzen, Yakuhai, Tanyao, Pinfu, Ipeko, Ryanpeko, Ikkitsukan ), Sanshoku Doujun, Sanshoku Doukou
    */
    void Test07()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL),
            new Ipeko("Ipeko", 1, 0, YakuType::N_PEKO),
            new Ryanpeko("Ryanpeko", 3, 1, YakuType::N_PEKO),
            new Ikkitsuukan("Ikkitsuukan", 2, 1, YakuType::GENERAL),
            new SanshokuDoujun("SanshokuDoujun", 2, 1, YakuType::GENERAL),
            new SanshokuDoukou("SanshokuDoukou", 2, 2, YakuType::GENERAL)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 2), *new NumberTile(NumberType::Dots, 3), *new NumberTile(NumberType::Dots, 4) }),
                },
                {
                    *new NumberTile(NumberType::Cracks, 3),
                    *new NumberTile(NumberType::Cracks, 2)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 4);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02 ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 2), *new NumberTile(NumberType::Dots, 3), *new NumberTile(NumberType::Dots, 4) }),
                },
                {
                    *new NumberTile(NumberType::Cracks, 4),
                    *new NumberTile(NumberType::Cracks, 2)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 3);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03 ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 2), *new NumberTile(NumberType::Dots, 3), *new NumberTile(NumberType::Dots, 4) }),
                },
                {
                    *new NumberTile(NumberType::Cracks, 5),
                    *new NumberTile(NumberType::Cracks, 6)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 4);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04 ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 5), *new NumberTile(NumberType::Cracks, 5) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 2) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 2), *new NumberTile(NumberType::Dots, 3) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 2),
                    *new NumberTile(NumberType::Dots, 2)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 2);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 05 ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 4), *new NumberTile(NumberType::Cracks, 4), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 4), *new NumberTile(NumberType::Bamboo, 4) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 6), *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8) }),
                    TileGroup(TileGroupType::Kangtsu, { *new NumberTile(NumberType::Dots, 4), *new NumberTile(NumberType::Dots, 4), *new NumberTile(NumberType::Dots, 4), *new NumberTile(NumberType::Dots, 4) }),
                },
                {
                    *new NumberTile(NumberType::Cracks, 5)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Cracks, 5);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
    }

    /*
    *  Yaku Test : ( Menzen, Yakuhai, Tanyao, Pinfu, Ipeko, Ryanpeko, Ikkitsukan, Sanshoku Doujun, Sanshoku Doukou ), Chanta, JunChanta, HonRoutou, ChinRoutou
    */
    void Test08()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL),
            new Ipeko("Ipeko", 1, 0, YakuType::N_PEKO),
            new Ryanpeko("Ryanpeko", 3, 1, YakuType::N_PEKO),
            new Ikkitsuukan("Ikkitsuukan", 2, 1, YakuType::GENERAL),
            new SanshokuDoujun("SanshokuDoujun", 2, 1, YakuType::GENERAL),
            new SanshokuDoukou("SanshokuDoukou", 2, 2, YakuType::GENERAL),
            new Chanta("Chanta", 2, 1, YakuType::CHANTA),
            new JunChanta("JunChanta", 3, 2, YakuType::CHANTA),
            new HonRoutou("HonRoutou", 2, 2, YakuType::CHANTA),
            new ChinRoutou("ChinRoutou", 13, 13, YakuType::YAKUMAN)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 9) }),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::White), *new DragonTile(DragonType::White), *new DragonTile(DragonType::White) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 9) }),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::White), *new DragonTile(DragonType::White), *new DragonTile(DragonType::White) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 1) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 2), *new NumberTile(NumberType::Cracks, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 2), *new NumberTile(NumberType::Dots, 3) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 1),
                    *new NumberTile(NumberType::Dots, 2)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 3);
            bool isMenzen = false;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 1) }),
                    TileGroup(TileGroupType::Kangtsu, { *new NumberTile(NumberType::Dots, 9), *new NumberTile(NumberType::Dots, 9), *new NumberTile(NumberType::Dots, 9), *new NumberTile(NumberType::Dots, 9) }),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::White), *new DragonTile(DragonType::White), *new DragonTile(DragonType::White) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 05  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 9), *new NumberTile(NumberType::Cracks, 9), *new NumberTile(NumberType::Cracks, 9) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 9), *new NumberTile(NumberType::Bamboo, 9), *new NumberTile(NumberType::Bamboo, 9) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 1), *new NumberTile(NumberType::Dots, 1) }),
                },
                {
                    *new NumberTile(NumberType::Dots, 9),
                    *new NumberTile(NumberType::Dots, 9)
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Dots, 9);
            bool isMenzen = false;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }


    }

    /*
    *  Yaku Test : ( Menzen, Yakuhai, Tanyao, Pinfu, Ipeko, Ryanpeko, Ikkitsukan, Sanshoku Doujun, Sanshoku Doukou, Chanta, JunChanta, HonRoutou, ChinRoutou ), Tsuuiisou, Honiisou, Chiniisou, Chitoitsu
    */
    void Test09()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL),
            new Ipeko("Ipeko", 1, 0, YakuType::N_PEKO),
            new Ryanpeko("Ryanpeko", 3, 1, YakuType::N_PEKO),
            new Ikkitsuukan("Ikkitsuukan", 2, 1, YakuType::GENERAL),
            new SanshokuDoujun("SanshokuDoujun", 2, 1, YakuType::GENERAL),
            new SanshokuDoukou("SanshokuDoukou", 2, 2, YakuType::GENERAL),
            new Chanta("Chanta", 2, 1, YakuType::CHANTA),
            new JunChanta("JunChanta", 3, 2, YakuType::CHANTA),
            new HonRoutou("HonRoutou", 2, 2, YakuType::CHANTA),
            new ChinRoutou("ChinRoutou", 13, 13, YakuType::YAKUMAN),
            new Tsuuiisou("Tsuuiisou", 13, 13, YakuType::YAKUMAN),
            new Honiisou("Honiisou", 3, 2, YakuType::IISOU),
            new Chiniisou("Chiniisou", 6, 5, YakuType::IISOU),
            new Chitoitsu("Chitoitsu", 2, 0, YakuType::GENERAL)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Koutsu, { *new WindTile(WindType::North), *new WindTile(WindType::North) }, *new WindTile(WindType::North), true),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::Red), *new DragonTile(DragonType::Red), *new DragonTile(DragonType::Red) }),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::White), *new DragonTile(DragonType::White), *new DragonTile(DragonType::White) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2)},  *new NumberTile(NumberType::Bamboo, 3), true),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::Red), *new DragonTile(DragonType::Red), *new DragonTile(DragonType::Red) }),
                    TileGroup(TileGroupType::Koutsu, { *new DragonTile(DragonType::White), *new DragonTile(DragonType::White), *new DragonTile(DragonType::White) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3)}),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 1), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 3)}),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 5), *new NumberTile(NumberType::Bamboo, 5), *new NumberTile(NumberType::Bamboo, 5)}),
                    TileGroup(TileGroupType::Shuntsu, { *new NumberTile(NumberType::Bamboo, 7), *new NumberTile(NumberType::Bamboo, 8), *new NumberTile(NumberType::Bamboo, 9)}),
                },
                {
                    *new NumberTile(NumberType::Bamboo, 9),
                }
            };
            TileCRef pickedTile = *new NumberTile(NumberType::Bamboo, 9);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Bamboo, 3), *new NumberTile(NumberType::Bamboo, 3) }),
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Dots, 7), *new NumberTile(NumberType::Dots, 7) }),
                    TileGroup(TileGroupType::Head, { *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8) }),
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::West), *new WindTile(WindType::West) }),

                },
                {
                    *new WindTile(WindType::East),
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
    }

    /*
    *  Yaku Test : ( Menzen, Yakuhai, Tanyao, Pinfu, Ipeko, Ryanpeko, Ikkitsukan, Sanshoku Doujun, Sanshoku Doukou, Chanta, JunChanta, HonRoutou, ChinRoutou, Tsuuiisou, Honiisou, Chiniisou, Chitoitsu ), Toitoi, Sanankou, Suuankou
    */
    void Test10()
    {
        std::vector<Yaku*> yakuList = {
            new Menzen("Menzen", 1, 0, YakuType::GENERAL),
            new Yakuhai("Yakuhai", 1, 1, YakuType::GENERAL),
            new Tanyao("Tanyao", 1, 1, YakuType::GENERAL),
            new Pinfu("Pinfu", 1, 0, YakuType::GENERAL),
            new Ipeko("Ipeko", 1, 0, YakuType::N_PEKO),
            new Ryanpeko("Ryanpeko", 3, 0, YakuType::N_PEKO),
            new Ikkitsuukan("Ikkitsuukan", 2, 1, YakuType::GENERAL),
            new SanshokuDoujun("SanshokuDoujun", 2, 1, YakuType::GENERAL),
            new SanshokuDoukou("SanshokuDoukou", 2, 2, YakuType::GENERAL),
            new Chanta("Chanta", 2, 1, YakuType::CHANTA),
            new JunChanta("JunChanta", 3, 2, YakuType::CHANTA),
            new HonRoutou("HonRoutou", 2, 2, YakuType::CHANTA),
            new ChinRoutou("ChinRoutou", 13, 13, YakuType::YAKUMAN),
            new Tsuuiisou("Tsuuiisou", 13, 13, YakuType::YAKUMAN),
            new Honiisou("Honiisou", 3, 2, YakuType::IISOU),
            new Chiniisou("Chiniisou", 6, 5, YakuType::IISOU),
            new Chitoitsu("Chitoitsu", 2, 0, YakuType::GENERAL),
            new Toitoi("Toitoi", 2, 2, YakuType::TOITOI),
            new Sanankou("Sanankou", 2, 2, YakuType::GENERAL),
            new Suuankou("Suuankou", 13, 0, YakuType::YAKUMAN)
        };

        {
            puts("[  Yaku Test 01  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = true;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 02  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = true;
            bool isRon    = false;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 03  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Kangtsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }, *new NumberTile(NumberType::Cracks, 1), true),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Cracks, 4), *new NumberTile(NumberType::Cracks, 4), *new NumberTile(NumberType::Cracks, 4) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }

        {
            puts("[  Yaku Test 04  ]");
            ReassembledTileGroup reassembledTileGroup = {
                { 
                    TileGroup(TileGroupType::Head, { *new WindTile(WindType::South), *new WindTile(WindType::South) }),
                    TileGroup(TileGroupType::Kangtsu, { *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1), *new NumberTile(NumberType::Cracks, 1) }, *new NumberTile(NumberType::Cracks, 1), true),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2), *new NumberTile(NumberType::Bamboo, 2) }),
                    TileGroup(TileGroupType::Koutsu, { *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8), *new NumberTile(NumberType::Dots, 8) }),
                },
                {
                    *new WindTile(WindType::East),
                    *new WindTile(WindType::East)
                }
            };
            TileCRef pickedTile = *new WindTile(WindType::East);
            bool isMenzen = false;
            bool isRon    = true;
            WindType roundWind = WindType::East;
            WindType selfWind  = WindType::West;
            
            CalcAndPrintYaku(yakuList, reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind);
        }
    }

    /* Utility for Test */
    void CalcAndPrintYaku(std::vector<Yaku*> yakuList, const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        printf(" ( RoundWind: %s, SelfWind: %s )\n", GetWindTypeString(roundWind).c_str(), GetWindTypeString(selfWind).c_str());
        printf("Tiles: ");
        for (auto tileGroup: reassembledTileGroup.tileGroupList)
        {
            tileGroup.Sort();
            printf("%s ", tileGroup.ToString().c_str());
        }
        for (const Tile& tile: reassembledTileGroup.restTiles)
        {
            printf("%s ", tile.ToString().c_str());
        }
        printf("    %s (%s)\n", pickedTile.ToString().c_str(), isRon ? "Ron" : "Tsumo");

        int totalScore = 0;
        std::vector<std::pair<Yaku*, int>> countedYakuList;
        for (auto& yaku: yakuList)
        {
            if (int score = yaku->GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind))
            {
                YakuType yakuType = yaku->GetYakuType();
                if (yakuType == YakuType::GENERAL)
                {
                    countedYakuList.emplace_back(std::pair<Yaku*, int>(yaku, score));
                    continue;
                }

                if (auto dup = std::find_if(countedYakuList.begin(), countedYakuList.end(), [&](std::pair<Yaku*,int>& y) { return y.first->GetYakuType() == yakuType; }); dup != countedYakuList.end())
                {
                    if (score > dup->second)
                    {
                        countedYakuList.erase(dup);
                        countedYakuList.emplace_back(std::pair<Yaku*, int>(yaku, score));
                    }
                }
                else
                {
                    countedYakuList.emplace_back(std::pair<Yaku*, int>(yaku, score));
                    continue;
                }
            }
        }

        // Yakuman post-process
        if (std::find_if(countedYakuList.begin(), countedYakuList.end(), [](const std::pair<Yaku*, int>& y){ return y.first->GetYakuType() == YakuType::YAKUMAN; }) != countedYakuList.end())
        {
            auto iter = std::find_if(countedYakuList.begin(), countedYakuList.end(), [](const std::pair<Yaku*, int>& y){ return y.first->GetYakuType() != YakuType::YAKUMAN; });
            while (iter != countedYakuList.end())
            {
                countedYakuList.erase(iter);
                iter = std::find_if(countedYakuList.begin(), countedYakuList.end(), [](const std::pair<Yaku*, int>& y){ return y.first->GetYakuType() != YakuType::YAKUMAN; });
            }
        }

        for (auto& yakuPair : countedYakuList)
        {
            printf("  <%s> %d\n", yakuPair.first->GetIdentifier().c_str(), yakuPair.second);
            totalScore += yakuPair.second;
        }


        printf("  Total Score : %d\n\n", totalScore);
    }

} // namespace Mini

#include <Test/Test.h>

#include <Source/Tile.h>
#include <Source/Hand.h>
#include <Source/Player.h>

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
        printf(" %s %s %s %s %s %s %s %s %s\n", NumberTile(NumberType::Dots, 1).ToString().c_str(), NumberTile(NumberType::Dots, 2).ToString().c_str(), NumberTile(NumberType::Dots, 3).ToString().c_str(), NumberTile(NumberType::Dots, 4).ToString().c_str(), NumberTile(NumberType::Dots, 5).ToString().c_str(), NumberTile(NumberType::Dots, 6).ToString().c_str(), NumberTile(NumberType::Dots, 7).ToString().c_str(), NumberTile(NumberType::Dots, 8).ToString().c_str(), NumberTile(NumberType::Dots, 9).ToString().c_str());
        printf(" %s %s %s %s %s %s %s %s %s\n\n", NumberTile(NumberType::Bamboo, 1).ToString().c_str(), NumberTile(NumberType::Bamboo, 2).ToString().c_str(), NumberTile(NumberType::Bamboo, 3).ToString().c_str(), NumberTile(NumberType::Bamboo, 4).ToString().c_str(), NumberTile(NumberType::Bamboo, 5).ToString().c_str(), NumberTile(NumberType::Bamboo, 6).ToString().c_str(), NumberTile(NumberType::Bamboo, 7).ToString().c_str(), NumberTile(NumberType::Bamboo, 8).ToString().c_str(), NumberTile(NumberType::Bamboo, 9).ToString().c_str());
        puts(" ================================= ");
    }

    /*
    *  Make tile list used to play game, and take 13 pieces randomly.
    */
    void Test02()
    {
        puts(" ========== < Test 02 > ========== ");
        std::vector<Tile *> tileList = GetCompleteTileLists();
        std::random_device rd; 
        std::mt19937 g(rd());
        std::shuffle(tileList.begin(), tileList.end(), g);

        Hand hand(std::vector<Tile*>(tileList.begin(), tileList.begin() + 13));
        hand.Sort();
        for (int i = 0; i < 13; ++i)
        {
            printf(" %s", hand.GetReadOnlyTiles()[i]->ToString().c_str());
        }
        printf("\n\n");

        for (auto& tile : tileList)
        {
            delete tile;
        }
        puts(" ================================= ");
    }

    /*
    *  One player game. Player just drops a tile and takes new one.
    */
    void Test03()
    {
        std::vector<Tile*> orgTileList = GetCompleteTileLists();
        std::vector<Tile*> tileList = orgTileList;
        std::random_device rd; 
        std::mt19937 g(rd());
        std::shuffle(tileList.begin(), tileList.end(), g);

        Player player(std::vector<Tile*>(tileList.begin(), tileList.begin() + 13));
        tileList = std::vector<Tile*>(tileList.begin() + 13, tileList.end());

        while (tileList.size() != 0)
        {
            Tile *newTile = tileList[tileList.size() - 1];
            tileList.pop_back();

            player.SortHand();
            const auto& handTiles = player.GetReadOnlyTiles();
            for (int i = 0; i < handTiles.size(); ++i)
            {
                printf("%s ", handTiles[i]->ToString().c_str());
            }
            printf("   %s\n", newTile->ToString().c_str());
            
            int index = -1;
            while (index < 0 || index > handTiles.size())
            {
                printf(" Index of tile to drop: ");
                scanf("%d", &index);
            }

            Tile *droppedTile = nullptr;
            if (index == handTiles.size())
            {
                // Tsumogiri
                droppedTile = newTile;
            }
            else
            {
                droppedTile = handTiles[index];
                player.DropTile(droppedTile);
                player.AddTile(newTile);
            }
            
            player.AddToDroppedTile(droppedTile);
            puts(" ----------------------------- ");
        }

        for (auto& tile : orgTileList)
        {
            delete tile;
        }

        puts(" ================================= ");
    }

} // namespace Mini
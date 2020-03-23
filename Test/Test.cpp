#include <Test/Test.h>

#include <Source/Tile.h>

#include <cstdio>

namespace Mini
{
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

    void Test02()
    {
        puts(" ========== < Test 02 > ========== ");
        std::vector<Tile *> tileList = GetCompleteTileLists();
        for (auto& tile : tileList)
        {
            printf(" %s", tile->ToString().c_str());
            delete tile;
        }
        puts(" ================================= ");
    }

} // namespace Mini
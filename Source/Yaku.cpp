#include <Source/Yaku.h>

#include <Source/Assert.h>

namespace Mini
{
    bool CheckChitoitsuPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<Tile*>& handTiles, const Tile* pickedTile, ReassembledTileGroup& result)
    {
        if (!calledTileGroupList.empty()) // Chitoitsu can't be made when it's not menzen state
        {
            return false;
        }

        // Simple Count Check
        std::vector<uint8_t> identifierList;
        for (auto& tile : handTiles)
        {
            identifierList.emplace_back(tile->GetIdentifier());
        } 
        identifierList.emplace_back(pickedTile->GetIdentifier());

        for (uint8_t identifier : identifierList)
        {
            int count = std::count(identifierList.begin(), identifierList.end(), identifier);
            if (count != 2 && count != 4)
            {
                return false;
            }
        }

        // It can be Chitoitsu
        std::vector<Tile*> tmp = handTiles;
        while (!tmp.empty())
        {
            Tile* firstTile = tmp.back();
            tmp.pop_back();

            auto secondTileIter = std::find_if(tmp.begin(), tmp.end(), [&](Tile* tile) { return tile->GetIdentifier() == firstTile->GetIdentifier(); });
            if (secondTileIter == tmp.end())
            {
                result.restTiles.emplace_back(*secondTileIter);
                continue;
            }

            result.tileGroupList.emplace_back(TileGroup(TileGroupType::Head, {firstTile, *secondTileIter}, nullptr, false));
        }

        return true;
    }

    bool CheckKokushimusouPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<Tile*>& handTiles, const Tile* pickedTile, ReassembledTileGroup& result)
    {
        if (!calledTileGroupList.empty()) // Kokushimusou can't be made when it's not menzen state
        {
            return false;
        }

        static const std::vector<uint8_t> constCheckTileIdentifierList = { 
            DragonTile(DragonType::White).GetIdentifier(),
            DragonTile(DragonType::Green).GetIdentifier(),
            DragonTile(DragonType::Red).GetIdentifier(),
            WindTile(WindType::East).GetIdentifier(),
            WindTile(WindType::South).GetIdentifier(),
            WindTile(WindType::West).GetIdentifier(),
            WindTile(WindType::North).GetIdentifier(),
            NumberTile(NumberType::Cracks, 1).GetIdentifier(),
            NumberTile(NumberType::Cracks, 9).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 1).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 9).GetIdentifier(),
            NumberTile(NumberType::Dots, 1).GetIdentifier(),
            NumberTile(NumberType::Dots, 9).GetIdentifier()
        };

        // Simple Check 
        for (auto& tile : handTiles)
        {
            if (std::find_if(constCheckTileIdentifierList.begin(), constCheckTileIdentifierList.end(), [&](uint8_t identifier){ return tile->GetIdentifier() == identifier; }) == constCheckTileIdentifierList.end())
            {
                return false;
            }
        }
        if (std::find_if(constCheckTileIdentifierList.begin(), constCheckTileIdentifierList.end(), [&](uint8_t identifier){ return pickedTile->GetIdentifier() == identifier; }) == constCheckTileIdentifierList.end())
        {
            return false;
        }

        std::vector<uint8_t> checkTileIdentifierList = { 
            DragonTile(DragonType::White).GetIdentifier(),
            DragonTile(DragonType::Green).GetIdentifier(),
            DragonTile(DragonType::Red).GetIdentifier(),
            WindTile(WindType::East).GetIdentifier(),
            WindTile(WindType::South).GetIdentifier(),
            WindTile(WindType::West).GetIdentifier(),
            WindTile(WindType::North).GetIdentifier(),
            NumberTile(NumberType::Cracks, 1).GetIdentifier(),
            NumberTile(NumberType::Cracks, 9).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 1).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 9).GetIdentifier(),
            NumberTile(NumberType::Dots, 1).GetIdentifier(),
            NumberTile(NumberType::Dots, 9).GetIdentifier()
        };

        bool once = true;
        for (auto& tile : handTiles)
        {
            auto iter = std::find_if(checkTileIdentifierList.begin(), checkTileIdentifierList.end(), [&](uint8_t identifier){ return tile->GetIdentifier() == identifier; });
            if (iter == checkTileIdentifierList.end())
            {
                if (std::exchange(once, false))
                {
                    result.restTiles.emplace_back(tile);
                }
                else // two same tiles appeared second time
                {
                    return false;
                }
            }
            else
            {
                result.restTiles.emplace_back(tile);
                checkTileIdentifierList.erase(iter);
            }
        }

        if (checkTileIdentifierList.empty())
        {
            // 13-way wating
            return true;
        }
        else if (checkTileIdentifierList[0] == pickedTile->GetIdentifier())
        {
            // common kokushimusou
            return true;
        }
        else
        {
            return false;
        }
    }
    
    Yaku::Yaku(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen) : 
        identifier(argIdentifier), menzenScore(argMenzenScore), score(argScore), shouldMenzen(argShouldMenzen)
    {

    }

    // Getters
    std::string Yaku::GetIdentifier() const
    {
        return identifier;
    }

    int Yaku::GetMenzenScore() const
    {
        return menzenScore;
    }

    int Yaku::GetScore() const
    {
        return score;
    }

    bool Yaku::GetShouldMenzen() const
    {
        return shouldMenzen;
    }

    bool Yaku::CanWin(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        // Common condition
        if (!isMenzen && GetScore() == 0)
        {
            return false;
        }

        return true;
    }


    /*
    *  Tangyao
    */
    bool Tangyao::CanWin(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (!Yaku::CanWin(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind))
        {
            return false;
        }
        
        static const std::vector<uint8_t> checkTileList = { 
            DragonTile(DragonType::White).GetIdentifier(), 
            DragonTile(DragonType::Green).GetIdentifier(), 
            DragonTile(DragonType::Red).GetIdentifier(),
            WindTile(WindType::East).GetIdentifier(),
            WindTile(WindType::South).GetIdentifier(),
            WindTile(WindType::West).GetIdentifier(),
            WindTile(WindType::North).GetIdentifier(),
            NumberTile(NumberType::Cracks, 1).GetIdentifier(),
            NumberTile(NumberType::Cracks, 9).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 1).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 9).GetIdentifier(),
            NumberTile(NumberType::Dots, 1).GetIdentifier(),
            NumberTile(NumberType::Dots, 9).GetIdentifier()
        };

        // Check if there are 1, 9, character tiles
        // if ()

        return false;
    }


} // namespace Mini
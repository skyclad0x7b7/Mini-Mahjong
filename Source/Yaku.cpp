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
            if (std::find(constCheckTileIdentifierList.begin(), constCheckTileIdentifierList.end(), tile->GetIdentifier()) == constCheckTileIdentifierList.end())
            {
                return false;
            }
        }
        if (std::find(constCheckTileIdentifierList.begin(), constCheckTileIdentifierList.end(), pickedTile->GetIdentifier()) == constCheckTileIdentifierList.end())
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
            auto iter = std::find(checkTileIdentifierList.begin(), checkTileIdentifierList.end(), tile->GetIdentifier());
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
    
    Yaku::Yaku(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : 
        identifier(argIdentifier), menzenScore(argMenzenScore), score(argScore), yakuType(argYakuType)
    {

    }

    // Getters
    std::string Yaku::GetIdentifier() const
    {
        return identifier;
    }

    YakuType Yaku::GetYakuType() const
    {
        return yakuType;
    }

    int Yaku::GetMenzenScore() const
    {
        return menzenScore;
    }

    int Yaku::GetScore() const
    {
        return score;
    }

    int Yaku::GetRealScore(bool isMenzen) const
    {
        return isMenzen ? GetMenzenScore() : GetScore();
    }

    int Yaku::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        // Common condition
        if (!isMenzen && GetScore() == 0)
        {
            return -1;
        }

        return 0;
    }

    /*
    *  Menzen
    */
    int Menzen::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        if (isMenzen && !isRon)
        {
            return GetRealScore(isMenzen);
        }

        return 0;
    }


    /*
    *  Tanyao
    */
    int Tanyao::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }
        
        static const std::vector<uint8_t> checkTileIdentifierList = { 
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
        for (auto& tileGroup : reassembledTileGroup.tileGroupList)
        {
            for (auto& tile : tileGroup.GetReadOnlyTiles())
            {
                if (std::find(checkTileIdentifierList.begin(), checkTileIdentifierList.end(), tile->GetIdentifier()) != checkTileIdentifierList.end())
                {
                    return 0;
                }
            }
        }

        for (auto& tile : reassembledTileGroup.restTiles)
        {
            if (std::find(checkTileIdentifierList.begin(), checkTileIdentifierList.end(), tile->GetIdentifier()) != checkTileIdentifierList.end())
            {
                return 0;
            }
        }

        if (std::find(checkTileIdentifierList.begin(), checkTileIdentifierList.end(), pickedTile->GetIdentifier()) != checkTileIdentifierList.end())
        {
            return 0;
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Yakuhai
    */
    int Yakuhai::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        int ret = 0;

        const std::vector<uint8_t> checkList = { DragonTile(DragonType::White).GetIdentifier(), DragonTile(DragonType::Green).GetIdentifier(), DragonTile(DragonType::Red).GetIdentifier(), 
                                                WindTile(roundWind).GetIdentifier(), WindTile(selfWind).GetIdentifier() };

        for (auto& tileGroup : reassembledTileGroup.tileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Koutsu || tileGroup.GetType() == TileGroupType::Kangtsu)
            {
                const uint8_t identifier = tileGroup.GetReadOnlyTiles()[0]->GetIdentifier();
                ret += std::count(checkList.begin(), checkList.end(), identifier) * GetRealScore(isMenzen);
            }
        }

        return ret;
    }

    /*
    *  Pinfu
    */
    int Pinfu::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        std::vector<uint8_t> checkList = { DragonTile(DragonType::White).GetIdentifier(), DragonTile(DragonType::Green).GetIdentifier(), DragonTile(DragonType::Red).GetIdentifier(),
                                        WindTile(roundWind).GetIdentifier(), WindTile(selfWind).GetIdentifier() };

        if (!isMenzen || reassembledTileGroup.restTiles.size() == 1)
        {
            return 0;
        }

        // Head Check
        auto headGroupIter = std::find_if(reassembledTileGroup.tileGroupList.begin(), reassembledTileGroup.tileGroupList.end(), [](const TileGroup& tg){ return tg.GetType() == TileGroupType::Head; });
        if (headGroupIter == reassembledTileGroup.tileGroupList.end())
        {
            return 0;
        }
        if (std::find(checkList.begin(), checkList.end(), headGroupIter->GetReadOnlyTiles()[0]->GetIdentifier()) != checkList.end())
        {
            return 0;
        }

        // Body Check
        bool once = true;
        for (auto& tileGroup : reassembledTileGroup.tileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Head)
            {
                if (std::exchange(once, false))
                {
                    continue;
                }
                else
                { // Head count over 2
                    return 0;
                }
            }
            
            if (tileGroup.GetType() != TileGroupType::Shuntsu)
            { // Pinfu can only be made by shuntsu
                return 0;
            }
        }

        // Rest Tile Check
        if (reassembledTileGroup.restTiles.size() != 2)
        {
            return 0;
        }
        std::vector<uint8_t> lastBodyIdList = { reassembledTileGroup.restTiles[0]->GetIdentifier(), reassembledTileGroup.restTiles[1]->GetIdentifier(), pickedTile->GetIdentifier() };
        std::sort(lastBodyIdList.begin(), lastBodyIdList.end());
        if ( (lastBodyIdList[2] - lastBodyIdList[1]) != 1 || (lastBodyIdList[1] - lastBodyIdList[0]) != 1 ||
                (lastBodyIdList[0] == lastBodyIdList[1] || lastBodyIdList[1] == lastBodyIdList[2]) )
        {
            return 0;
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Ipeko
    */
    int Ipeko::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>       restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile->GetIdentifier() != restTileList[0]->GetIdentifier()) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1], pickedTile }, nullptr, false));
            }
        }

        // Sort TileGroups
        for (auto& tileGroup : tmpTileGroupList)
        {
            tileGroup.Sort();
        }

        for (int i = 0; i < tileGroupList.size() - 1; ++i)
        {
            if (tileGroupList[i].GetType() != TileGroupType::Shuntsu)
            {
                continue;
            }

            for (int j = i + 1; j < tileGroupList.size(); ++j)
            {
                if (tileGroupList[j].GetType() != TileGroupType::Shuntsu)
                {
                    continue;
                }

                const std::vector<Tile*>& firstTileList  = tileGroupList[i].GetReadOnlyTiles();
                const std::vector<Tile*>& secondTileList = tileGroupList[j].GetReadOnlyTiles();
                if (firstTileList[0]->GetIdentifier() == secondTileList[0]->GetIdentifier() &&
                    firstTileList[1]->GetIdentifier() == secondTileList[1]->GetIdentifier() &&
                    firstTileList[2]->GetIdentifier() == secondTileList[2]->GetIdentifier())
                {
                    return GetRealScore(isMenzen);
                }
            }
        }

        return 0;
    }


} // namespace Mini
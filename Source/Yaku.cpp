#include <Source/Yaku.h>

#include <Source/Assert.h>

#include <map>

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

        // Simple Check 
        for (auto& tile : handTiles)
        {
            if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()) == YaochuuTileIdList.end())
            {
                return false;
            }
        }
        if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), pickedTile->GetIdentifier()) == YaochuuTileIdList.end())
        {
            return false;
        }

        std::vector<uint8_t> checkTileIdentifierList = YaochuuTileIdList;

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

        // Check if there are 1, 9, character tiles
        for (auto& tileGroup : reassembledTileGroup.tileGroupList)
        {
            for (auto& tile : tileGroup.GetReadOnlyTiles())
            {
                if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()) != YaochuuTileIdList.end())
                {
                    return 0;
                }
            }
        }

        for (auto& tile : reassembledTileGroup.restTiles)
        {
            if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()) != YaochuuTileIdList.end())
            {
                return 0;
            }
        }

        if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), pickedTile->GetIdentifier()) != YaochuuTileIdList.end())
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

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile->GetIdentifier() == restTileList[0]->GetIdentifier()) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1], pickedTile }, nullptr, false));
            }
        }

        int ret = 0;

        const std::vector<uint8_t> checkList = { DragonTile(DragonType::White).GetIdentifier(), DragonTile(DragonType::Green).GetIdentifier(), DragonTile(DragonType::Red).GetIdentifier(), 
                                                WindTile(roundWind).GetIdentifier(), WindTile(selfWind).GetIdentifier() };

        for (auto& tileGroup : tmpTileGroupList)
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
        if ( lastBodyIdList[0] == lastBodyIdList[1] ) // Not shuntsu
        {
            return 0;
        }

        if ( lastBodyIdList[1] == pickedTile->GetIdentifier() ) // Middle-Tile wating
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
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

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

        for (int i = 0; i < tmpTileGroupList.size() - 1; ++i)
        {
            if (tmpTileGroupList[i].GetType() != TileGroupType::Shuntsu)
            {
                continue;
            }

            for (int j = i + 1; j < tmpTileGroupList.size(); ++j)
            {
                if (tmpTileGroupList[j].GetType() != TileGroupType::Shuntsu)
                {
                    continue;
                }

                const std::vector<Tile*>& firstTileList  = tmpTileGroupList[i].GetReadOnlyTiles();
                const std::vector<Tile*>& secondTileList = tmpTileGroupList[j].GetReadOnlyTiles();
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

    /*
    *  Ryanpeko
    */
    int Ryanpeko::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

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
            if (tileGroup.GetType() == TileGroupType::Koutsu || tileGroup.GetType() == TileGroupType::Kangtsu)
            {
                return false;
            }
            tileGroup.Sort();
        }

        int ipekoCount = 0;
        for (int i = 0; i < tmpTileGroupList.size() - 1; ++i)
        {
            if (tmpTileGroupList[i].GetType() != TileGroupType::Shuntsu)
            {
                continue;
            }

            for (int j = i + 1; j < tmpTileGroupList.size(); ++j)
            {
                if (tmpTileGroupList[j].GetType() != TileGroupType::Shuntsu)
                {
                    continue;
                }

                const std::vector<Tile*>& firstTileList  = tmpTileGroupList[i].GetReadOnlyTiles();
                const std::vector<Tile*>& secondTileList = tmpTileGroupList[j].GetReadOnlyTiles();
                if (firstTileList[0]->GetIdentifier() == secondTileList[0]->GetIdentifier() &&
                    firstTileList[1]->GetIdentifier() == secondTileList[1]->GetIdentifier() &&
                    firstTileList[2]->GetIdentifier() == secondTileList[2]->GetIdentifier())
                {
                    ++ipekoCount;
                }
            }
        }

        if (ipekoCount == 2)
        {
            return GetRealScore(isMenzen);
        }

        return 0;
    }

    /*
    *  Ikkitsuukan
    */
    int Ikkitsuukan::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile->GetIdentifier() != restTileList[0]->GetIdentifier()) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1], pickedTile }, nullptr, false));
            }
        }
        
        std::map<NumberType, uint8_t> ikkitsuukanPair = { {NumberType::Cracks, 0}, {NumberType::Bamboo, 0}, {NumberType::Dots, 0} };
        for (auto tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() != TileGroupType::Shuntsu)
            {
                continue;
            }

            tileGroup.Sort();
            NumberTile *first  = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[0]);
            NumberTile *second = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[1]);
            NumberTile *third  = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[2]);
            debug_assert(first  != nullptr, "tile must be number tile");
            debug_assert(second != nullptr, "tile must be number tile");
            debug_assert(third  != nullptr, "tile must be number tile");

            if (first->GetNumber() == 1 && second->GetNumber() == 2 && third->GetNumber() == 3)
            {
                ikkitsuukanPair[first->GetType()] |= 0b001;
            }
            else if (first->GetNumber() == 4 && second->GetNumber() == 5 && third->GetNumber() == 6)
            {
                ikkitsuukanPair[first->GetType()] |= 0b010;
            }
            else if (first->GetNumber() == 7 && second->GetNumber() == 8 && third->GetNumber() == 9)
            {
                ikkitsuukanPair[first->GetType()] |= 0b100;
            }   
        }

        for (auto iter : ikkitsuukanPair)
        {
            if (iter.second == 0b111)
            {
                return GetRealScore(isMenzen);
            }
        }

        return 0;
    }

    /*
    *  Sanshoku Doujun
    */
    int SanshokuDoujun::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile->GetIdentifier() != restTileList[0]->GetIdentifier()) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1], pickedTile }, nullptr, false));
            }
        }

        std::map<uint32_t, uint8_t> sanshokuDoujunPair;
        for (auto tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() != TileGroupType::Shuntsu)
            {
                continue;
            }

            tileGroup.Sort();
            NumberTile *first  = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[0]);
            NumberTile *second = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[1]);
            NumberTile *third  = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[2]);
            debug_assert(first  != nullptr, "tile must be number tile");
            debug_assert(second != nullptr, "tile must be number tile");
            debug_assert(third  != nullptr, "tile must be number tile");

            int key = first->GetNumber() | second->GetNumber() << 2 | third->GetNumber() << 4;
            if (auto iter = sanshokuDoujunPair.find(key); iter !=sanshokuDoujunPair.end())
            {
                switch(first->GetType())
                {
                case NumberType::Cracks:
                    iter->second |= 0b001;
                    break;
                case NumberType::Bamboo:
                    iter->second |= 0b010;
                    break;
                case NumberType::Dots:
                    iter->second |= 0b100;
                    break;
                }
            }
            else
            {
                switch(first->GetType())
                {
                case NumberType::Cracks:
                    sanshokuDoujunPair[key] = 0b001;
                    break;
                case NumberType::Bamboo:
                    sanshokuDoujunPair[key] = 0b010;
                    break;
                case NumberType::Dots:
                    sanshokuDoujunPair[key] = 0b100;
                    break;
                }
            }
        }

        for (auto iter : sanshokuDoujunPair)
        {
            if (iter.second == 0b111)
            {
                return GetRealScore(isMenzen);
            }
        }

        return 0;
    }

    /*
    *  Sanshoku Doukou
    */
    int SanshokuDoukou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile->GetIdentifier() == restTileList[0]->GetIdentifier()) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1], pickedTile }, nullptr, false));
            }
        }

        std::map<uint8_t, uint8_t> sanshokuDoukouPair;
        for (auto tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() != TileGroupType::Koutsu && tileGroup.GetType() != TileGroupType::Kangtsu)
            {
                continue;
            }

            NumberTile *first  = dynamic_cast<NumberTile*>(tileGroup.GetReadOnlyTiles()[0]);
            if (first == nullptr) // It's not NumberTile
            {
                continue;
            }

            int key = first->GetNumber();
            if (auto iter = sanshokuDoukouPair.find(key); iter != sanshokuDoukouPair.end())
            {
                switch(first->GetType())
                {
                case NumberType::Cracks:
                    iter->second |= 0b001;
                    break;
                case NumberType::Bamboo:
                    iter->second |= 0b010;
                    break;
                case NumberType::Dots:
                    iter->second |= 0b100;
                    break;
                }
            }
            else
            {
                switch(first->GetType())
                {
                case NumberType::Cracks:
                    sanshokuDoukouPair[key] = 0b001;
                    break;
                case NumberType::Bamboo:
                    sanshokuDoukouPair[key] = 0b010;
                    break;
                case NumberType::Dots:
                    sanshokuDoukouPair[key] =  0b100;
                    break;
                }
            }
        }

        for (auto iter : sanshokuDoukouPair)
        {
            if (iter.second == 0b111)
            {
                return GetRealScore(isMenzen);
            }
        }
        
        return 0;
    }

    /*
    *  Chanta
    */
    int Chanta::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            bool found = false;
            for (auto& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (auto iter = std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()); iter != YaochuuTileIdList.end())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return 0;
            }
        }

        // Check RestTileList
        bool found = std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), pickedTile->GetIdentifier()) != YaochuuTileIdList.end();
        for (auto& tile : restTileList)
        {
            if (auto iter = std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()); iter != YaochuuTileIdList.end())
            {
                found = true;
                break;
            } 
        } 
        if (!found)
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  JunChanta
    */
    int JunChanta::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            bool found = false;
            for (auto& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (auto iter = std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), tile->GetIdentifier()); iter != RoutouTileIdList.end())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return 0;
            }
        }

        // Check RestTileList
        bool found = std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), pickedTile->GetIdentifier()) != RoutouTileIdList.end();
        for (auto& tile : restTileList)
        {
            if (auto iter = std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), tile->GetIdentifier()); iter != RoutouTileIdList.end())
            {
                found = true;
                break;
            } 
        } 
        if (!found)
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  HonRoutou
    */
    int HonRoutou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            for (auto& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (auto iter = std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()); iter == YaochuuTileIdList.end())
                {
                    return 0;
                }
            }
        }

        // Check RestTileList
        for (auto& tile : restTileList)
        {
            if (auto iter = std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), tile->GetIdentifier()); iter == YaochuuTileIdList.end())
            {
                return 0;
            } 
        }

        // Check PickedTile
        if (std::find(YaochuuTileIdList.begin(), YaochuuTileIdList.end(), pickedTile->GetIdentifier()) == YaochuuTileIdList.end())
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  ChinRoutou
    */
    int ChinRoutou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<Tile*>&      restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            for (auto& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (auto iter = std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), tile->GetIdentifier()); iter == RoutouTileIdList.end())
                {
                    return 0;
                }
            }
        }

        // Check RestTileList
        for (auto& tile : restTileList)
        {
            if (auto iter = std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), tile->GetIdentifier()); iter == RoutouTileIdList.end())
            {
                return 0;
            } 
        }

        // Check PickedTile
        if (std::find(RoutouTileIdList.begin(), RoutouTileIdList.end(), pickedTile->GetIdentifier()) == RoutouTileIdList.end())
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }


} // namespace Mini
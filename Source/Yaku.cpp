#include <Source/Yaku.h>

#include <Source/Assert.h>

#include <algorithm>
#include <map>

namespace
{
    template <typename Cont>
    auto FindIdentifier(const Cont& container, const Mini::Tile& tile)
    {
        return std::find(container.begin(), container.end(), tile);
    }

    template <typename Cont>
    bool InIdentifierList(const Cont& container, const Mini::Tile& tile)
    {
        return FindIdentifier(container, tile) != container.end();
    }
}

namespace Mini
{
    bool CheckChitoitsuPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<TileCRef>& handTiles, const Tile& pickedTile, ReassembledTileGroup& result)
    {
        if (!calledTileGroupList.empty()) // Chitoitsu can't be made when it's not menzen state
        {
            return false;
        }

        // Simple Count Check
        std::vector<uint8_t> identifierList;
        for (const Tile& tile : handTiles)
        {
            identifierList.emplace_back(tile);
        } 
        identifierList.emplace_back(pickedTile);

        for (uint8_t identifier : identifierList)
        {
            int count = std::count(identifierList.begin(), identifierList.end(), identifier);
            if (count != 2 && count != 4)
            {
                return false;
            }
        }

        // It can be Chitoitsu
        std::vector<TileCRef> tmp = handTiles;
        while (!tmp.empty())
        {
            const Tile& firstTile = tmp.back();
            tmp.pop_back();

            auto secondTileIter = FindIdentifier(tmp, firstTile);
            if (secondTileIter == tmp.end())
            {
                result.restTiles.emplace_back(*secondTileIter);
                continue;
            }


            result.tileGroupList.emplace_back(TileGroupType::Head, std::vector { TileCRef(firstTile), *secondTileIter });
        }

        return true;
    }

    bool CheckKokushimusouPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<TileCRef>& handTiles, const Tile& pickedTile, ReassembledTileGroup& result)
    {
        if (!calledTileGroupList.empty()) // Kokushimusou can't be made when it's not menzen state
        {
            return false;
        }

        // Simple Check 
        for (const Tile& tile : handTiles)
        {
            if (!InIdentifierList(YaochuuTileIdList, tile))
            {
                return false;
            }
        }
        if (!InIdentifierList(YaochuuTileIdList, pickedTile))
        {
            return false;
        }

        std::vector<uint8_t> checkTileIdentifierList = YaochuuTileIdList;

        bool once = true;
        for (const Tile& tile : handTiles)
        {
            auto iter = FindIdentifier(checkTileIdentifierList, tile);
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
        else if (checkTileIdentifierList[0] == pickedTile)
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

    int Yaku::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
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
    int Menzen::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
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
    int Tanyao::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        // Check if there are 1, 9, character tiles
        for (auto& tileGroup : reassembledTileGroup.tileGroupList)
        {
            for (const Tile& tile : tileGroup.GetReadOnlyTiles())
            {
                if (InIdentifierList(YaochuuTileIdList, tile))
                {
                    return 0;
                }
            }
        }

        for (const Tile& tile : reassembledTileGroup.restTiles)
        {
            if (InIdentifierList(YaochuuTileIdList, tile))
            {
                return 0;
            }
        }

        if (InIdentifierList(YaochuuTileIdList, pickedTile))
        {
            return 0;
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Yakuhai
    */
    int Yakuhai::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile == restTileList[0]) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
            }
        }

        int ret = 0;

        const std::vector<uint8_t> checkList = { DragonTile(DragonType::White), DragonTile(DragonType::Green), DragonTile(DragonType::Red), WindTile(roundWind), WindTile(selfWind) };

        for (auto& tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Koutsu || tileGroup.GetType() == TileGroupType::Kangtsu)
            {
                const uint8_t identifier = static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]);
                ret += std::count(checkList.begin(), checkList.end(), identifier) * GetRealScore(isMenzen);
            }
        }

        return ret;
    }

    /*
    *  Pinfu
    */
    int Pinfu::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        std::vector<uint8_t> checkList = { DragonTile(DragonType::White), DragonTile(DragonType::Green), DragonTile(DragonType::Red), WindTile(roundWind), WindTile(selfWind) };

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
        if (InIdentifierList(checkList, headGroupIter->GetReadOnlyTiles()[0]))
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
        std::vector<uint8_t> lastBodyIdList = { static_cast<const Tile&>(reassembledTileGroup.restTiles[0]), static_cast<const Tile&>(reassembledTileGroup.restTiles[1]), pickedTile };
        std::sort(lastBodyIdList.begin(), lastBodyIdList.end());
        if (lastBodyIdList[0] == lastBodyIdList[1]) // Not shuntsu
        {
            return 0;
        }

        if (lastBodyIdList[1] == pickedTile) // Middle-Tile wating
        {
            return 0;
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Ipeko
    */
    int Ipeko::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile != restTileList[0]) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
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

                const std::vector<TileCRef>& firstTileList  = tmpTileGroupList[i].GetReadOnlyTiles();
                const std::vector<TileCRef>& secondTileList = tmpTileGroupList[j].GetReadOnlyTiles();
                if (firstTileList[0] == secondTileList[0] &&
                    firstTileList[1] == secondTileList[1] &&
                    firstTileList[2] == secondTileList[2])
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
    int Ryanpeko::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile != restTileList[0]) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
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

                const std::vector<TileCRef>& firstTileList  = tmpTileGroupList[i].GetReadOnlyTiles();
                const std::vector<TileCRef>& secondTileList = tmpTileGroupList[j].GetReadOnlyTiles();
                if (firstTileList[0] == secondTileList[0] &&
                    firstTileList[1] == secondTileList[1] &&
                    firstTileList[2] == secondTileList[2])
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
    int Ikkitsuukan::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile != restTileList[0]) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
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
            try {
                auto const& first  = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]));
                auto const& second = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[1]));
                auto const& third  = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[2]));

                if (first.GetNumber() == 1 && second.GetNumber() == 2 && third.GetNumber() == 3)
                {
                    ikkitsuukanPair[first.GetType()] |= 0b001;
                }
                else if (first.GetNumber() == 4 && second.GetNumber() == 5 && third.GetNumber() == 6)
                {
                    ikkitsuukanPair[first.GetType()] |= 0b010;
                }
                else if (first.GetNumber() == 7 && second.GetNumber() == 8 && third.GetNumber() == 9)
                {
                    ikkitsuukanPair[first.GetType()] |= 0b100;
                }   
            } catch (const std::bad_cast&) {
                debug_assert(false, "tile must be number tile");
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
    int SanshokuDoujun::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile != restTileList[0]) // Shuntsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Shuntsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
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
            try {
                const auto& first  = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]));
                const auto& second = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[1]));
                const auto& third  = dynamic_cast<const NumberTile&>(static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[2]));

                const int key = first.GetNumber() | second.GetNumber() << 2 | third.GetNumber() << 4;
                if (auto iter = sanshokuDoujunPair.find(key); iter !=sanshokuDoujunPair.end())
                {
                    switch(first.GetType())
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
                    default:
                        assert_unreachable();
                    }
                }
                else
                {
                    switch(first.GetType())
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
                    default:
                        assert_unreachable();
                    }
                }
            } catch (std::bad_cast const&) {
                debug_assert(false, "tile must be number tile");
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
    int SanshokuDoukou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile == restTileList[0]) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
            }
        }

        std::map<uint8_t, uint8_t> sanshokuDoukouPair;
        for (auto tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() != TileGroupType::Koutsu && tileGroup.GetType() != TileGroupType::Kangtsu)
            {
                continue;
            }

            // used pointer to check if it's number tile
            // to avoid using try catch for branching
            auto const* first_ptr  = dynamic_cast<const NumberTile*>(&static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]));
            if (first_ptr == nullptr) // It's not NumberTile
            {
                continue;
            }
            const auto& first(*first_ptr);

            int key = first.GetNumber();
            if (auto iter = sanshokuDoukouPair.find(key); iter != sanshokuDoukouPair.end())
            {
                switch(first.GetType())
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
                default:
                    assert_unreachable();
                }
            }
            else
            {
                switch(first.GetType())
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
                default:
                    assert_unreachable();
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
    int Chanta::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            bool found = false;
            for (const Tile& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (const auto iter = FindIdentifier(YaochuuTileIdList, tile); iter != YaochuuTileIdList.end())
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
        bool found = InIdentifierList(YaochuuTileIdList, pickedTile);
        for (const Tile& tile : restTileList)
        {
            if (InIdentifierList(YaochuuTileIdList, tile))
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
    int JunChanta::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            bool found = false;
            for (const Tile& tile : tileGroup.GetReadOnlyTiles())
            {
                if (InIdentifierList(RoutouTileIdList, tile))
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
        bool found = InIdentifierList(RoutouTileIdList, pickedTile);
        for (const Tile& tile : restTileList)
        {
            if (InIdentifierList(RoutouTileIdList, tile))
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
    int HonRoutou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            for (const Tile& tile : tileGroup.GetReadOnlyTiles()) 
            {
                if (!InIdentifierList(YaochuuTileIdList, tile))
                {
                    return 0;
                }
            }
        }

        // Check RestTileList
        for (const Tile& tile : restTileList)
        {
            if (!InIdentifierList(YaochuuTileIdList, tile))
            {
                return 0;
            } 
        }

        // Check PickedTile
        if (!InIdentifierList(YaochuuTileIdList, pickedTile))
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  ChinRoutou
    */
    int ChinRoutou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            for (const Tile& tile : tileGroup.GetReadOnlyTiles())
            {
                if (!InIdentifierList(RoutouTileIdList, tile))
                {
                    return 0;
                }
            }
        }

        // Check RestTileList
        for (const Tile& tile : restTileList)
        {
            if (!InIdentifierList(RoutouTileIdList, tile))
            {
                return 0;
            } 
        }

        // Check PickedTile
        if (!InIdentifierList(RoutouTileIdList, pickedTile))
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  Tsuuiisou
    */
    int Tsuuiisou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;
        
        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            // Don't need to check all tiles in TileGroup
            if (!InIdentifierList(JiTileIdList, tileGroup.GetReadOnlyTiles()[0]))
            {
                return 0;
            }
        }

        // Check RestTileList & PickedTile
        // Don't need to check all tiles in RestTile and PickedTile
        if (!InIdentifierList(JiTileIdList, pickedTile))
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  Honiisou
    */
    int Honiisou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        NumberType numberType = NumberType::None;

        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            const auto* tile_ptr = dynamic_cast<const NumberTile*>(&static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]));
            if (tile_ptr == nullptr)
            {
                continue;
            }

            const auto& tile = *tile_ptr;
            if (numberType == NumberType::None)
            {
                numberType = tile.GetType();
            }
            else
            {
                if (numberType != tile.GetType())
                {
                    return 0;
                }
            }
        }

        // Check RestTileList & PickedTile
        // Don't need to check all tiles in RestTile and PickedTile
        if (const auto* tile_ptr = dynamic_cast<const NumberTile*>(&pickedTile); tile_ptr != nullptr)
        {
            const auto& tile = *tile_ptr;
            if (numberType == NumberType::None)
            {
                numberType = tile.GetType();
            }
            else if (numberType != tile.GetType())
            {
                return 0;
            }
        }

        // Check if there's any number tile or not
        if (numberType == NumberType::None)
        {
            return 0;
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Chiniisou
    */
    int Chiniisou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        NumberType numberType = NumberType::None;

        // Check TileGroupList
        for (auto& tileGroup : tileGroupList)
        {
            const auto* tile_ptr = dynamic_cast<const NumberTile*>(&static_cast<const Tile&>(tileGroup.GetReadOnlyTiles()[0]));
            if (tile_ptr == nullptr)
            {
                return 0;
            }
            const auto& tile = *tile_ptr;
            if (numberType == NumberType::None)
            {
                numberType = tile.GetType();
            }
            else
            {
                if (numberType != tile.GetType())
                {
                    return 0;
                }
            }
        }

        // Check RestTileList & PickedTile
        // Don't need to check all tiles in RestTile and PickedTile
        auto const* tile_ptr = dynamic_cast<const NumberTile*>(&pickedTile);
        if (tile_ptr != nullptr)
        {
            auto const& tile = *tile_ptr;
            if (numberType == NumberType::None)
            {
                numberType = tile.GetType();
            }
            else if (numberType != tile.GetType())
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }

        // Check if there's any number tile or not
        if (numberType == NumberType::None)
        {
            return 0;
        }
        
        return GetRealScore(isMenzen);
    }

    /*
    *  Chitoitsu
    */
    int Chitoitsu::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        if (!isMenzen) // Chitoitsu must be in Menzen state
        {
            return 0;
        }

        if (restTileList.size() != 1) // Chitoitsu must wait for Head
        {
            return 0;
        }

        for (auto& tileGroup : tileGroupList)
        {
            if (tileGroup.GetType() != TileGroupType::Head)
            {
                return 0;
            }
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Toitoi
    */
    int Toitoi::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile == restTileList[0]) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
            }
        }

        for (auto& tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Shuntsu)
            {
                return 0;
            }
        }

        return GetRealScore(isMenzen);
    }

    /*
    *  Sanankou
    */
    int Sanankou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile == restTileList[0]) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
            }
        }

        int count = 0;
        for (auto& tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Koutsu || tileGroup.GetType() == TileGroupType::Kangtsu)
            {
                if (!tileGroup.GetIsCalled())
                {
                    count++;
                }
            }
        }

        if (count == 3)
        {
            return GetRealScore(isMenzen);
        }

        return 0;
    }

    /*
    *  Suuankou
    */
    int Suuankou::GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind)
    {
        if (Yaku::GetScoreIfPossible(reassembledTileGroup, pickedTile, isMenzen, isRon, roundWind, selfWind) != 0)
        {
            return 0;
        }

        const std::vector<TileGroup>& tileGroupList = reassembledTileGroup.tileGroupList;
        const std::vector<TileCRef>& restTileList = reassembledTileGroup.restTiles;

        // Add pickedTile into tileGroup if needed
        std::vector<TileGroup> tmpTileGroupList = tileGroupList;
        if (restTileList.size() == 2) // Last one is body
        {
            if (pickedTile == restTileList[0]) // Koutsu Check
            {
                tmpTileGroupList.emplace_back(TileGroup(TileGroupType::Koutsu, { restTileList[0], restTileList[1] }, pickedTile, isRon));
            }
        }

        int count = 0;
        for (auto& tileGroup : tmpTileGroupList)
        {
            if (tileGroup.GetType() == TileGroupType::Koutsu || tileGroup.GetType() == TileGroupType::Kangtsu)
            {
                if (!tileGroup.GetIsCalled())
                {
                    count++;
                }
            }
        }

        if (count == 4)
        {
            return GetRealScore(isMenzen);
        }

        return 0;
    }
} // namespace Mini

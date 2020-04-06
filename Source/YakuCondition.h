#ifndef __MINI_MAHJONG_YAKU_CONDITION_H__
#define __MINI_MAHJONG_YAKU_CONDITION_H__

#include <Source/TileGroup.h>

#include <string>
#include <vector>

namespace Mini
{
    enum class YakuConditionType
    {
        Tile,
        TileGroup
    };

    class YakuCondition
    {
    private:
        int priority;
        YakuConditionType ycType;
        std::vector<TileGroupType> tgTypeList;
        bool shouldMenzen;
        
    public:
        // Setters
        void SetPriority(int value);
        void SetConditionType(YakuConditionType type);
        void SetTileGroupTypeList(std::vector<TileGroupType> typeList);

        // Getters
        int GetPriority() const;
        YakuConditionType GetYakuConditionType() const;
        std::vector<TileGroupType> GetTileGroupTypeList() const;
    };
}

#endif // __MINI_MAHJONG_YAKU_CONDITION_H__
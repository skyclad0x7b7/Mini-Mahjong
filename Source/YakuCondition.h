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
        std::vector<TileGroupType> tgType;
    public:
        

    };
}

#endif // __MINI_MAHJONG_YAKU_CONDITION_H__
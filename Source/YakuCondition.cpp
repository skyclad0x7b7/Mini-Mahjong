#include <Source/YakuCondition.h>

namespace Mini
{
    YakuCondition::YakuCondition()
    {

    }

    // Setters
    void YakuCondition::SetPriority(int value)
    {
        priority = value;
    }

    void YakuCondition::SetConditionType(YakuConditionType type)
    {
        tcType = type;
    }

    void YakuCondition::SetTileGroupTypeList(std::vector<TileGroupType> typeList)
    {
        tgTypeList = typeList;
    }

    // Getters
    int YakuCondition::GetPriority() const
    {
        return priority;
    }

    YakuConditionType YakuCondition::GetYakuConditionType() const
    {
        return tcType;
    }

    std::vector<TileGroupType> YakuCondition::GetTileGroupTypeList() const
    {
        return tgTypeList;
    }

} // namespace Mini

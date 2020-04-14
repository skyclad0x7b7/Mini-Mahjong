#ifndef __MINI_MAHJONG_CONSTANT_H__
#define __MINI_MAHJONG_CONSTANT_H__

#include <vector>
#include <string>

namespace Mini
{
    enum class DragonType
    {
        White = 0,
        Green = 1,
        Red   = 2,
    };

    enum class WindType
    {
        East  = 0,
        South = 1,
        West  = 2,
        North = 3
    };

    static const std::vector<WindType> WindTypeList = { WindType::East, WindType::South, WindType::West, WindType::North };

    std::string GetWindTypeString(WindType type);

    enum class NumberType
    {
        None = 0,
        Cracks = 1,
        Bamboo = 2,
        Dots   = 3,
    };

    static const std::vector<NumberType> NumberTypeList = { NumberType::Cracks, NumberType::Bamboo, NumberType::Dots };


} // namespace Mini

#endif // __MINI_MAHJONG_CONSTANT_H__
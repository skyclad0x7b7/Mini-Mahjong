#ifndef __MINI_MAHJONG_CONSTANT_H__
#define __MINI_MAHJONG_CONSTANT_H__

#pragma once

namespace Mini
{
    enum class DragonType
    {
        White = 0,
        Green = 1,
        Red   = 2,
    }

	enum class WindType
    {
        East  = 0,
        South = 1,
        West  = 2,
        North = 3
    };

    enum class NumberType
    {
        Cracks = 0,
        Dots   = 1,
        Bamboo = 2
    }
} // namespace Mini

#endif // __MINI_MAHJONG_CONSTANT_H__
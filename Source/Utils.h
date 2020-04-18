#ifndef __MINI_MAHJONG_UTILS_H__
#define __MINI_MAHJONG_UTILS_H__

#include <Source/Tile.h>

#include <stdio.h>
#include <vector>

namespace Mini
{
    
#ifdef MINI_MAHJONG_DEBUG
#define dbgprint(fmt, args...) printf(fmt, ##args)
#else
#define dbgprint(fmt, args...)
#endif
    
    void SortTiles(std::vector<const Tile *>& tileList);

}

#endif // __MINI_MAHJONG_UTILS_H__
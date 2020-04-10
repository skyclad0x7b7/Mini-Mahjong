#ifndef __MINI_MAHJONG_UTILS_H__
#define __MINI_MAHJONG_UTILS_H__

#include <stdio.h>

namespace Mini
{
    
#ifdef MINI_MAHJONG_DEBUG
#define dbgprint(fmt, args...) printf(fmt, ##args)
#else
#define dbgprint(fmt, args...)
#endif

}

#endif // __MINI_MAHJONG_UTILS_H__
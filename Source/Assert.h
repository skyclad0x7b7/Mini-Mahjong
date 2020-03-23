// For unknown reason, we can't use assert in cassert now

#ifndef __MINI_MAHJONG_ASSERT_H__
#define __MINI_MAHJONG_ASSERT_H__

#include <cstdio>

#ifdef MINI_MAHJONG_DEBUG
#define debug_assert(cond, message) if(!(cond)) { puts(message); exit(0); }
#else
#define debug_assert(cond, message)
#endif

#define noway_assert(cond, message) if(!(cond)) { puts(message); exit(0); }

#define assert_unreachable() noway_assert(false, "Unreachable code!");

#endif // __MINI_MAHJONG_ASSERT_H__
#ifndef __MINI_MAHJONG_ASSERT_H__
#define __MINI_MAHJONG_ASSERT_H__

#include <cassert>

#ifdef MINI_MAHJONG_DEBUG
#define debug_assert(cond, message) assert((cond && message))
#else
#define debug_assert(cond, message)
#endif

#define noway_assert(cond, message) assert((cond && message))

#define assert_unreachable() assert(false, "Unreachable code!");

#endif // __MINI_MAHJONG_ASSERT_H__
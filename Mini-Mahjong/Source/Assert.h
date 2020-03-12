#ifndef __MINI_MAHJONG_ASSERT_H__
#define __MINI_MAHJONG_ASSERT_H__

#ifdef MINI_DEBUG
#define debug_assert(cond, message) assert((cond && message))
#else
#define debug_assert(cond, message)
#endif

#endif // __MINI_MAHJONG_ASSERT_H__
#ifndef __MINI_MAHJONG_TEST_H__
#define __MINI_MAHJONG_TEST_H__

#include <Source/Yaku.h>

#include <vector>

namespace Mini
{
    void Test01();
    void Test02();
    void Test03();
    void Test04();
    void Test05();
    void Test06();
    void Test07();
    void Test08();

    /* Utility for Test */
    void CalcAndPrintYaku(std::vector<Yaku*> yakuList, const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
}

#endif // __MINI_MAHJONG_TEST_H__
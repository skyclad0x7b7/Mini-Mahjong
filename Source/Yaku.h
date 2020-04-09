#ifndef __MINI_MAHJONG_YAKU_H__
#define __MINI_MAHJONG_YAKU_H__

#include <Source/TileGroup.h>

#include <string>

namespace Mini
{
    struct ReassembledTileGroup
    {
        std::vector<TileGroup> tileGroupList;
        std::vector<Tile*> restTiles;
    };

    bool CheckChitoitsuPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<Tile*>& handTiles, const Tile* pickedTile, ReassembledTileGroup& result);
    bool CheckKokushimusouPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<Tile*>& handTiles, const Tile* pickedTile, ReassembledTileGroup& result);

    class Yaku
    {
    private:
        Yaku(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen);
        
        std::string identifier;
        int menzenScore;
        int score;
        bool shouldMenzen;

    public:
        // Getters
        std::string GetIdentifier() const;
        int GetMenzenScore() const;
        int GetScore() const;
        bool GetShouldMenzen() const;

        virtual bool CanWin(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind) = 0;
    };

    class Tangyao : Yaku
    {
    public:
        Tangyao(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen);
        virtual bool CanWin(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };



}

#endif // __MINI_MAHJONG_YAKU_H__
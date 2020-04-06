#ifndef __MINI_MAHJONG_YAKU_H__
#define __MINI_MAHJONG_YAKU_H__

#include <Source/YakuCondition.h>

#include <string>

namespace Mini
{
    class Yaku
    {
    private:
        Yaku::Yaku(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen);
        
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

        virtual bool CanWin(const std::vector<TileGroup*>& calledTileGroup, const std::vector<Tile*>& leftTiles, const Tile* pickedTile, bool isMenzen, bool isRon) = 0;
    };

    class Tangyao : Yaku
    {
    public:
        Tangyao::Tangyao(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen);
        virtual bool CanWin(const std::vector<Tile*>& handTiles, const std::vector<Tile*>& droppedTiles, const std::vector<TileGroup*>& calledTileGroup, bool isMenzen, bool isRon);
    }



}

#endif // __MINI_MAHJONG_YAKU_H__
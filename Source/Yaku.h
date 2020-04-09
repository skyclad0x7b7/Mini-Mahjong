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
        std::string identifier;
        int menzenScore;
        int score;

    protected:
        Yaku(std::string argIdentifier, int argMenzenScore, int argScore);

    public:
        // Getters
        std::string GetIdentifier() const;
        int GetMenzenScore() const;
        int GetScore() const;

        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind) = 0;
    };

    class Menzen : public Yaku
    {
    public:
        Menzen(std::string argIdentifier, int argMenzenScore, int argScore) : Yaku(argIdentifier, argMenzenScore, argScore) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Yakuhai : public Yaku
    {
    public:
        Yakuhai(std::string argIdentifier, int argMenzenScore, int argScore) : Yaku(argIdentifier, argMenzenScore, argScore) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Tanyao : public Yaku
    {
    public:
        Tanyao(std::string argIdentifier, int argMenzenScore, int argScore) : Yaku(argIdentifier, argMenzenScore, argScore) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Pinfu : public Yaku
    {
    public:
        Pinfu(std::string argIdentifier, int argMenzenScore, int argScore) : Yaku(argIdentifier, argMenzenScore, argScore) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

}

#endif // __MINI_MAHJONG_YAKU_H__
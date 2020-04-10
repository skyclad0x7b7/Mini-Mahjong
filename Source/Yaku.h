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

    /*
    *  Some Yaku, such as Ipeko and Ryanpeko can't be counted at the same time
    */
    enum class YakuType
    {
        GENERAL = 0,
        N_PEKO,
        CHANTA,
        TOITOI,
        YAKUMAN,
    };

    class Yaku
    {
    private:
        std::string identifier;
        YakuType yakuType;
        int menzenScore;
        int score;

    protected:
        Yaku(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType);

    public:
        // Getters
        std::string GetIdentifier() const;
        YakuType GetYakuType() const;
        int GetMenzenScore() const;
        int GetScore() const;
        int GetRealScore(bool isMenzen) const;

        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind) = 0;
    };

    class Menzen : public Yaku
    {
    public:
        Menzen(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Yakuhai : public Yaku
    {
    public:
        Yakuhai(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Tanyao : public Yaku
    {
    public:
        Tanyao(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Pinfu : public Yaku
    {
    public:
        Pinfu(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Ipeko : public Yaku
    {
    public:
        Ipeko(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, Tile* pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

}

#endif // __MINI_MAHJONG_YAKU_H__
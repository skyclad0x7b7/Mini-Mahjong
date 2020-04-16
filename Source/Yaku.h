#ifndef __MINI_MAHJONG_YAKU_H__
#define __MINI_MAHJONG_YAKU_H__

#include <Source/TileGroup.h>

#include <string>

namespace Mini
{
    struct ReassembledTileGroup
    {
        std::vector<TileGroup> tileGroupList;
        std::vector<TileCRef> restTiles;
    };

    bool CheckChitoitsuPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<TileCRef>& handTiles, const Tile& pickedTile, ReassembledTileGroup& result);
    bool CheckKokushimusouPossible(const std::vector<TileGroup>& calledTileGroupList, const std::vector<TileCRef>& handTiles, const Tile& pickedTile, ReassembledTileGroup& result);

    /*
    *  Some Yaku, such as Ipeko and Ryanpeko can't be counted at the same time
    */
    enum class YakuType
    {
        GENERAL = 0,
        N_PEKO,
        CHANTA,
        IISOU,
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

        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind) = 0;
    };

    class Menzen : public Yaku
    {
    public:
        Menzen(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Yakuhai : public Yaku
    {
    public:
        Yakuhai(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Tanyao : public Yaku
    {
    public:
        Tanyao(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Pinfu : public Yaku
    {
    public:
        Pinfu(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Ipeko : public Yaku
    {
    public:
        Ipeko(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Ryanpeko : public Yaku
    {
    public:
        Ryanpeko(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Ikkitsuukan : public Yaku
    {
    public:
        Ikkitsuukan(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class SanshokuDoujun : public Yaku
    {
    public:
        SanshokuDoujun(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class SanshokuDoukou : public Yaku
    {
    public:
        SanshokuDoukou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Chanta : public Yaku
    {
    public:
        Chanta(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class JunChanta : public Yaku
    {
    public:
        JunChanta(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class HonRoutou : public Yaku
    {
    public:
        HonRoutou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class ChinRoutou : public Yaku
    {
    public:
        ChinRoutou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Tsuuiisou : public Yaku
    {
    public:
        Tsuuiisou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Honiisou : public Yaku
    {
    public:
        Honiisou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Chiniisou : public Yaku
    {
    public:
        Chiniisou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Chitoitsu : public Yaku
    {
    public:
        Chitoitsu(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Toitoi : public Yaku
    {
    public:
        Toitoi(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Sanankou : public Yaku
    {
    public:
        Sanankou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };

    class Suuankou : public Yaku
    {
    public:
        Suuankou(std::string argIdentifier, int argMenzenScore, int argScore, YakuType argYakuType) : Yaku(argIdentifier, argMenzenScore, argScore, argYakuType) { };
        virtual int GetScoreIfPossible(const ReassembledTileGroup& reassembledTileGroup, const Tile& pickedTile, bool isMenzen, bool isRon, WindType roundWind, WindType selfWind);
    };
}

#endif // __MINI_MAHJONG_YAKU_H__

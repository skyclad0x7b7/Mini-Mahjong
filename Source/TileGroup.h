#ifndef __MINI_MAHJONG_TILEGROUP_H__
#define __MINI_MAHJONG_TILEGROUP_H__

#include <Source/Tile.h>

#include <vector>

namespace Mini
{
    enum class TileGroupType
    {
        Shuntsu,
        Koutsu,
        Kangtsu
    };

    class TileGroup
    {
    private:
        std::vector<Tile*> tgTiles;
        TileGroupType tgType;
        bool isOpened = false;
    public:
        TileGroup(const TileGroupType type, const std::vector<Tile*>& tiles, Tile *called = nullptr);

        // Setters
        void SetType(const TileGroupType type);
        void SetIsOpened(const bool value);

        // Getters
        TileGroupType GetType() const;
        bool GetIsOpened() const;
    };

} // namespace Mini

#endif // __MINI_MAHJONG_TILEGROUP_H__
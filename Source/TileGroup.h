#ifndef __MINI_MAHJONG_TILEGROUP_H__
#define __MINI_MAHJONG_TILEGROUP_H__

#include <Source/Tile.h>

#include <vector>

namespace Mini
{
    enum class TileGroupType
    {
        Head,       // Head Type
        Shuntsu,
        Koutsu,
        Kangtsu
    };

    class TileGroup
    {
    private:
        std::vector<Tile*> tgTiles;
        TileGroupType tgType;
        bool isCalled = false;
    public:
        TileGroup(const TileGroupType type, const std::vector<Tile*>& tiles, Tile *calledTile = nullptr, bool argIsCalled = false);

        // Setters
        void SetType(const TileGroupType type);
        void SetIsCalled(const bool value);

        // Getters
        TileGroupType GetType() const;
        bool GetIsCalled() const;
        const std::vector<Tile*>& GetReadOnlyTiles() const;
        
        std::string ToString() const;

        void Sort();
    };

} // namespace Mini

#endif // __MINI_MAHJONG_TILEGROUP_H__
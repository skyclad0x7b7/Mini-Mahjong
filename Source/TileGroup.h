#ifndef __MINI_MAHJONG_TILEGROUP_H__
#define __MINI_MAHJONG_TILEGROUP_H__

#include <Source/Tile.h>

#include <optional>
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
        std::vector<TileCRef> tgTiles;
        TileGroupType tgType;
        bool isCalled = false;
    public:
        TileGroup(const TileGroupType type, const std::vector<TileCRef>& tiles, const std::optional<TileCRef>& calledTile = std::nullopt, bool argIsCalled = false);

        // Setters
        void SetType(const TileGroupType type);
        void SetIsCalled(const bool value);

        // Getters
        TileGroupType GetType() const;
        bool GetIsCalled() const;
        const std::vector<TileCRef>& GetReadOnlyTiles() const;
        
        std::string ToString() const;

        void Sort();
    };

    using TileGroupRef = std::reference_wrapper<TileGroup>;
    using TileGroupCRef = std::reference_wrapper<const TileGroup>;

} // namespace Mini

#endif // __MINI_MAHJONG_TILEGROUP_H__

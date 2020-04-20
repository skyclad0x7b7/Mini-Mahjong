#ifndef __MINI_MAHJONG_REASSEMBLED_TILEGROUP_H__
#define __MINI_MAHJONG_REASSEMBLED_TILEGROUP_H__

#include <Source/Tile.h>
#include <Source/TileGroup.h>

#include <vector>

namespace Mini
{

    class ReassembledTileGroup
    {
    private:
        std::vector<TileGroup> tileGroupList;
        std::vector<const Tile *> restTiles;
    public:
        ReassembledTileGroup() = default;
        ReassembledTileGroup(const std::vector<TileGroup>& argTGList, const std::vector<const Tile*>& argRestTiles);

        void InsertTileGroup(TileGroup tileGroup);
        void InsertRestTiles(const std::vector<const Tile *>& tiles);
        void InsertRestTile(const Tile *tile);

        const std::vector<TileGroup>& GetReadOnlyTileGroupList() const;
        const std::vector<const Tile *>      GetReadOnlyRestTiles() const;

        int GetCountTileGroup() const;
        int GetCountTileGroup(TileGroupType type) const;

        void SortTileGroupList();
        std::string GetIdentifier();
    };

} // namespace Mini

#endif // __MINI_MAHJONG_REASSEMBLED_TILEGROUP_H__
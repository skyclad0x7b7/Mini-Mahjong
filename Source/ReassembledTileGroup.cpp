#include <Source/ReassembledTileGroup.h>
#include <Source/Utils.h>

#include <algorithm>

namespace Mini
{
    ReassembledTileGroup::ReassembledTileGroup(const std::vector<TileGroup>& argTGList, const std::vector<const Tile*>& argRestTiles)
    {
        tileGroupList = argTGList;
        restTiles     = argRestTiles;
    }

    void ReassembledTileGroup::InsertTileGroup(TileGroup tileGroup)
    {
        tileGroupList.emplace_back(tileGroup);
    }

    void ReassembledTileGroup::InsertRestTiles(const std::vector<const Tile *>& tiles)
    {
        restTiles.insert(restTiles.end(), tiles.begin(), tiles.end());
    }

    void ReassembledTileGroup::InsertRestTile(const Tile *tile)
    {
        restTiles.emplace_back(tile);
    }

    const std::vector<TileGroup>& ReassembledTileGroup::GetReadOnlyTileGroupList() const
    {
        return tileGroupList;
    }

    const std::vector<const Tile *> ReassembledTileGroup::GetReadOnlyRestTiles() const
    {
        return restTiles;
    }

    int ReassembledTileGroup::GetCountTileGroup() const
    {
        return tileGroupList.size();
    }

    int ReassembledTileGroup::GetCountTileGroup(TileGroupType type) const
    {
        return std::count_if(tileGroupList.begin(), tileGroupList.end(), [type](const TileGroup& tg){ return tg.GetType() == type; });
    }

    void ReassembledTileGroup::SortTileGroupList()
    {
        Mini::SortTileGroupList(tileGroupList);
    }

    std::string ReassembledTileGroup::GetIdentifier()
    {
        SortTileGroupList();
        std::string ret;
        for (auto& tg : tileGroupList)
        {
            for (auto& tile : tg.GetReadOnlyTiles())
            {
                ret += tile->GetIdentifier();
            }
        }
        return ret;
    }
}
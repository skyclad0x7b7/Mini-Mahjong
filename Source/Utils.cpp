#include <Source/Utils.h>

#include <algorithm>

namespace Mini
{
    void SortTiles(std::vector<const Tile *>& tileList)
    {
        std::sort(tileList.begin(), tileList.end(), [](const Tile *first, const Tile *second) { return first->GetIdentifier() < second->GetIdentifier(); });
    }

    void SortTileGroupList(std::vector<TileGroup>& tileGroupList)
    {
        std::sort(tileGroupList.begin(), tileGroupList.end(), [](const TileGroup& first, const TileGroup& second) { return first.GetIdentifier() < second.GetIdentifier(); });
    }
} // namespace Mini
#include <Source/Utils.h>

#include <algorithm>

namespace Mini
{
    void SortTiles(std::vector<Tile*>& tileList)
    {
        std::sort(tileList.begin(), tileList.end(), [](const Tile* first, const Tile* second) { return first->GetIdentifier() < second->GetIdentifier(); });
    }
} // namespace Mini
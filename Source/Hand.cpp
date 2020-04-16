#include <Source/Hand.h>
#include <Source/Assert.h>
#include <Source/Utils.h>

#include <algorithm>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    Hand::Hand(const std::vector<TileCRef>& initTiles)
    {
        debug_assert(initTiles.size() == 13, "Tiles count must be 13");
        handTiles = initTiles;
    }

    const std::vector<TileCRef>& Hand::GetReadOnlyTiles() const
    {
        return handTiles;
    }
    
    void Hand::AddTile(const Tile& tile)
    {
        handTiles.emplace_back(tile);
    }

    void Hand::RemoveTile(const Tile& tile)
    {
        auto iter = std::find(handTiles.begin(), handTiles.end(), tile);
        debug_assert(iter != handTiles.end(), "Can't find tile to remove");
        handTiles.erase(iter);
    }

    void Hand::Sort()
    {
        SortTiles(handTiles);
    }

} // namespace Mini

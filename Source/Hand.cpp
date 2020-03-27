#include <Source/Hand.h>
#include <Source/Assert.h>

#include <algorithm>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    Hand::Hand(const std::vector<Tile*>& initTiles)
    {
        debug_assert(initTiles.size() == 13, "Tiles count must be 13");
        handTiles = initTiles;
    }

    const std::vector<Tile*>& Hand::GetTiles() const
    {
        return handTiles;
    }
    
    void Hand::AddTile(Tile *tile)
    {
        handTiles.emplace_back(tile);
    }

    void Hand::RemoveTile(Tile *tile)
    {
        auto iter = std::find(handTiles.begin(), handTiles.end(), tile);
        debug_assert(iter != handTiles.end(), "Can't find tile to remove");
        handTiles.erase(iter);
    }

    void Hand::Sort()
    {
        std::sort(handTiles.begin(), handTiles.end(), [](Tile* first, Tile* second){ return first->GetIdentifier() < second->GetIdentifier(); });
    }

} // namespace Mini
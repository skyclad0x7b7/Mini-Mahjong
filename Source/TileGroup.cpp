#include <Source/TileGroup.h>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    TileGroup::TileGroup(const TileGroupType type, const std::vector<Tile*>& tiles, Tile *called)
    {
        tgType = type;
        tgTiles = tiles;

        if (called)
        {
            tgTiles.emplace_back(called);
            isOpened = true;
        }
        else
        {
            // Assume it's Ankan
            isOpened = false;
        }
    }

    // Setters
    void TileGroup::SetType(const TileGroupType type)
    {
        tgType = type;
    }

    void TileGroup::SetIsOpened(const bool value)
    {
        isOpened = value;
    }

    // Getters
    TileGroupType TileGroup::GetType() const
    {
        return tgType;
    }

    bool TileGroup::GetIsOpened() const
    {
        return isOpened;
    }
    
} // namespace Mini
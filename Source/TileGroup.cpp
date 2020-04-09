#include <Source/TileGroup.h>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    TileGroup::TileGroup(const TileGroupType type, const std::vector<Tile*>& tiles, Tile *calledTile, bool isCalled)
    {
        tgType = type;
        tgTiles = tiles;

        if (calledTile)
        {
            tgTiles.emplace_back(calledTile);
        }

        isOpened = isCalled;
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

    const std::vector<Tile*>& TileGroup::GetReadOnlyTiles() const
    {
        return tgTiles;
    }

    
} // namespace Mini
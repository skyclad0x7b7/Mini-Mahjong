#include <Source/TileGroup.h>

#include <Source/Assert.h>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    TileGroup::TileGroup(const TileGroupType type, const std::vector<Tile*>& tiles, Tile *calledTile, bool isCalled)
    {
        tgType = type;
        tgTiles = tiles;

        if (type == TileGroupType::Head)
        {
            debug_assert(tiles.size() == 2, "Head's tiles count must be 2");
            debug_assert(tiles[0]->GetIdentifier() == tiles[1]->GetIdentifier(), "Head tiles must be same");
            debug_assert(calledTile == nullptr, "Head can't be called");
            debug_assert(isCalled == false, "Head can't be called");
        }

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

    std::string TileGroup::ToString() const
    {
        std::string ret;
        for (auto& tile : tgTiles)
        {
            ret += tile->ToString() + " ";
        }
        return ret;
    }

    void TileGroup::Sort()
    {
        std::sort(tgTiles.begin(), tgTiles.end(), [](Tile* first, Tile* second){ return first->GetIdentifier() < second->GetIdentifier(); });
    }

} // namespace Mini
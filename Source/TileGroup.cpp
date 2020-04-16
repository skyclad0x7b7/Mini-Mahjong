#include <Source/TileGroup.h>
#include <Source/Assert.h>
#include <Source/Utils.h>

namespace Mini
{
    // ==================================================
    // class TileGroup implementation
    // ==================================================
    TileGroup::TileGroup(const TileGroupType type, const std::vector<TileCRef>& tiles, const std::optional<TileCRef>& calledTile, bool argIsCalled)
    {
        auto tmpTiles = tiles;

        if (calledTile)
        {
            tmpTiles.emplace_back(calledTile.value());
        }

        SortTiles(tmpTiles);

        if (type == TileGroupType::Head)
        {
            debug_assert(tmpTiles.size() == 2, "Head's tiles count must be 2");
            debug_assert(tmpTiles[0] == tmpTiles[1], "Head's tiles must be same");
            debug_assert(calledTile == std::nullopt, "Head can't be called");
            debug_assert(argIsCalled == false, "Head can't be called");
        }

        if (type == TileGroupType::Koutsu)
        {
            debug_assert(tmpTiles.size() == 3, "Koutsu's tiles count must be 3");
            debug_assert(tmpTiles[0] == tmpTiles[1] && tmpTiles[1] == tmpTiles[2], "Koutsu's tiles must be same");
        }

        if (type == TileGroupType::Kangtsu)
        {
            debug_assert(tmpTiles.size() == 4, "Kangtsu's tiles count must be 3");
            debug_assert(tmpTiles[0] == tmpTiles[1] && tmpTiles[1] == tmpTiles[2] && tmpTiles[2] == tmpTiles[3], "Kangtsu's tiles must be same");
        }

        if (type == TileGroupType::Shuntsu)
        {
            debug_assert(tmpTiles.size() == 3, "Shuntsu's tiles count must be 3");
            debug_assert((tmpTiles[2] - tmpTiles[1]) == 1 && (tmpTiles[1] - tmpTiles[0]) == 1, "Shuntsu's tiles must be consecutive");
        }

        tgType = type;
        tgTiles = tmpTiles;
        isCalled = argIsCalled;
    }

    // Setters
    void TileGroup::SetType(const TileGroupType type)
    {
        tgType = type;
    }

    void TileGroup::SetIsCalled(const bool value)
    {
        isCalled = value;
    }

    // Getters
    TileGroupType TileGroup::GetType() const
    {
        return tgType;
    }

    bool TileGroup::GetIsCalled() const
    {
        return isCalled;
    }

    const std::vector<TileCRef>& TileGroup::GetReadOnlyTiles() const
    {
        return tgTiles;
    }

    std::string TileGroup::ToString() const
    {
        std::string ret;
        for (const Tile& tile : tgTiles)
        {
            ret += tile.ToString() + " ";
        }
        return ret;
    }

    void TileGroup::Sort()
    {
        SortTiles(tgTiles);
    }

} // namespace Mini

#include <Source/Player.h>

#include <Source/Utils.h>
#include <Source/Assert.h>

namespace Mini
{
    // ==================================================
    // class Player implementation
    // ==================================================
    Player::Player(const std::vector<const Tile *>& initTiles)
    {
        debug_assert(initTiles.size() == 13, "Tiles count must be 13");
        handTiles = initTiles;
    }

    const std::vector<const Tile *>& Player::GetReadOnlyTiles() const
    {
        return handTiles;
    }

    const std::vector<const Tile *>& Player::GetReadOnlyDroppedTiles() const
    {
        return droppedTiles;
    }

    const std::vector<TileGroup>& Player::GetReadOnlyCalledTileGroup() const
    {
        return calledTileGroup;
    }
    
    void Player::AddTile(const Tile *tile)
    {
        handTiles.emplace_back(tile);
    }

    void Player::DropTile(const Tile *tile)
    {
        auto iter = std::find(handTiles.begin(), handTiles.end(), tile);
        debug_assert(iter != handTiles.end(), "Can't find tile to remove");
        handTiles.erase(iter);
    }

    void Player::AddToDroppedTile(const Tile *tile)
    {
        droppedTiles.emplace_back(tile);
    }

    void Player::SortHandTiles()
    {
        SortTiles(handTiles);
    }

    void Player::SetIsMenzen(bool value)
    {
        isMenzen = value;
    }

    bool Player::GetIsMenzen() const
    {
        return isMenzen;
    }

    void Player::OnOtherPlayerDroppedTile(const Tile *tile)
    {
        // Check Ron
        
        // Check Calling (Chi, Pong, Kang)


    }


} // namespace Mini
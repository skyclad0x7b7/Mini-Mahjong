#include <Source/Player.h>

namespace Mini
{
    // ==================================================
    // class Player implementation
    // ==================================================
    Player::Player(const std::vector<TileCRef>& initTiles) : pHand(initTiles)
    {
        
    }

    const std::vector<TileCRef>& Player::GetReadOnlyTiles() const
    {
        return pHand.GetReadOnlyTiles();
    }

    const std::vector<TileCRef>& Player::GetReadOnlyDroppedTiles() const
    {
        return droppedTiles;
    }

    const std::vector<TileGroup>& Player::GetReadOnlyCalledTileGroup() const
    {
        return calledTileGroup;
    }
    
    void Player::AddTile(const TileCRef& tile)
    {
        pHand.AddTile(tile);
    }

    void Player::DropTile(const TileCRef& tile)
    {
        pHand.RemoveTile(tile);
    }

    void Player::AddToDroppedTile(const TileCRef& tile)
    {
        droppedTiles.emplace_back(tile);
    }

    void Player::SortHand()
    {
        pHand.Sort();
    }

    void Player::SetIsMenzen(bool value)
    {
        isMenzen = value;
    }

    bool Player::GetIsMenzen() const
    {
        return isMenzen;
    }

    void Player::OnOtherPlayerDroppedTile(const TileCRef& tile)
    {
        // Check Ron
        
        // Check Calling (Chi, Pong, Kang)


    }


} // namespace Mini

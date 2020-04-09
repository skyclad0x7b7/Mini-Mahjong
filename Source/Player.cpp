#include <Source/Player.h>

namespace Mini
{
    // ==================================================
    // class Player implementation
    // ==================================================
    Player::Player(const std::vector<Tile*>& initTiles) : pHand(initTiles)
    {
        
    }

    const std::vector<Tile*>& Player::GetReadOnlyTiles() const
    {
        return pHand.GetReadOnlyTiles();
    }

    const std::vector<Tile*>& Player::GetReadOnlyDroppedTiles() const
    {
        return droppedTiles;
    }

    const std::vector<TileGroup>& Player::GetReadOnlyCalledTileGroup() const
    {
        return calledTileGroup;
    }
    
    void Player::AddTile(Tile* tile)
    {
        pHand.AddTile(tile);
    }

    void Player::DropTile(const Tile* tile)
    {
        pHand.RemoveTile(tile);
    }

    void Player::AddToDroppedTile(Tile* tile)
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

    void Player::OnOtherPlayerDroppedTile(Tile* tile)
    {
        // Check Ron
        
        // Check Calling (Chi, Pong, Kang)


    }


} // namespace Mini
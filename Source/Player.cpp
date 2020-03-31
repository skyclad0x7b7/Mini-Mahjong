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


} // namespace Mini
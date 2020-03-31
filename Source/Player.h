#ifndef __MINI_MAHJONG_PLAYER_H__
#define __MINI_MAHJONG_PLAYER_H__

#include <Source/Hand.h>
#include <Source/TileGroup.h>

#include <vector>

namespace Mini
{
    class Player
    {
    private:
        Hand pHand;
        std::vector<TileGroup> pCalledTileGroup;
        std::vector<Tile*> droppedTiles;

    public:
        Player(const std::vector<Tile*>& initTiles);

        const std::vector<Tile*>& GetReadOnlyTiles() const;

        void AddTile(Tile* tile);
        void DropTile(const Tile* tile);
        void AddToDroppedTile(Tile* tile);

        void SortHand();

        // Event Handler
        void OnOtherPlayerDroppedTile();
    };

} // namespace

#endif // __MINI_MAHJONG_PLAYER_H__
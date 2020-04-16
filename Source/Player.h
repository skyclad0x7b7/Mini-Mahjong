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
        std::vector<TileGroup> calledTileGroup;
        std::vector<TileCRef> droppedTiles;
        bool isMenzen;

        int pScore;
    public:
        Player(const std::vector<TileCRef>& initTiles);

        const std::vector<TileCRef>& GetReadOnlyTiles() const;
        const std::vector<TileCRef>& GetReadOnlyDroppedTiles() const;
        const std::vector<TileGroup>& GetReadOnlyCalledTileGroup() const;
        
        void AddTile(const Tile& tile);
        void DropTile(const Tile& tile);
        void AddToDroppedTile(const Tile& tile);

        void SortHand();

        void SetIsMenzen(bool value);
        bool GetIsMenzen() const;

        // Event Handler
        void OnOtherPlayerDroppedTile(const Tile& tile);
        void OnOtherPlayerCalledKang(const Tile& tile);

    };

} // namespace

#endif // __MINI_MAHJONG_PLAYER_H__

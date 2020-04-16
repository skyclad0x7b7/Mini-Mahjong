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
        
        void AddTile(const TileCRef& tile);
        void DropTile(const TileCRef& tile);
        void AddToDroppedTile(const TileCRef& tile);

        void SortHand();

        void SetIsMenzen(bool value);
        bool GetIsMenzen() const;

        // Event Handler
        void OnOtherPlayerDroppedTile(const TileCRef& tile);
        void OnOtherPlayerCalledKang(const TileCRef& tile);

    };

} // namespace

#endif // __MINI_MAHJONG_PLAYER_H__

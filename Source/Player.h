#ifndef __MINI_MAHJONG_PLAYER_H__
#define __MINI_MAHJONG_PLAYER_H__

#include <Source/Tile.h>
#include <Source/TileGroup.h>

#include <vector>

namespace Mini
{
    class Player
    {
    private:
        std::vector<const Tile *> handTiles;
        std::vector<const Tile *> droppedTiles;
        std::vector<TileGroup> calledTileGroup;
        bool isMenzen;

        int pScore;
    public:
        Player(const std::vector<const Tile *>& initTiles);

        const std::vector<const Tile *>& GetReadOnlyTiles() const;
        const std::vector<const Tile *>& GetReadOnlyDroppedTiles() const;
        const std::vector<TileGroup>& GetReadOnlyCalledTileGroup() const;
        
        void AddTile(const Tile *tile);
        void DropTile(const Tile *tile);
        void AddToDroppedTile(const Tile *tile);

        void SortHandTiles();

        void SetIsMenzen(bool value);
        bool GetIsMenzen() const;

        // Event Handler
        void OnOtherPlayerDroppedTile(const Tile *tile);
        void OnOtherPlayerCalledKang(const Tile *tile);

    };

} // namespace

#endif // __MINI_MAHJONG_PLAYER_H__
#ifndef __MINI_MAHJONG_HAND_H__
#define __MINI_MAHJONG_HAND_H__

#include <Source/Tile.h>

#include <vector>

namespace Mini
{
    class Hand
    {
    private:
        std::vector<const Tile *> handTiles;
    public:
        Hand(const std::vector<const Tile *>& initTiles);

        // Getters
        const std::vector<const Tile *>& GetReadOnlyTiles() const;
        
        void AddTile(const Tile *tile);
        void RemoveTile(const Tile *tile);

        void Sort();
    };


} // namespace Mini

#endif // __MINI_MAHJONG_HAND_H__
#ifndef __MINI_MAHJONG_HAND_H__
#define __MINI_MAHJONG_HAND_H__

#include <Source/Tile.h>

#include <vector>

namespace Mini
{
    class Hand
    {
    private:
        std::vector<Tile*> handTiles;
    public:
        Hand(const std::vector<Tile*>& initTiles);

        // Getters
        const std::vector<Tile*>& GetTiles() const;
        
        void AddTile(Tile *tile);
        void RemoveTile(Tile *tile);

        void Sort();
    };


} // namespace Mini

#endif // __MINI_MAHJONG_HAND_H__
#ifndef __MINI_MAHJONG_HAND_H__
#define __MINI_MAHJONG_HAND_H__

#include <Tile.h>

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
    };


} // namespace Mini

#endif // __MINI_MAHJONG_HAND_H__
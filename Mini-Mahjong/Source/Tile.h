#ifndef __MINI_MAHJONG_TILE_H__
#define __MINI_MAHJONG_TILE_H__

#include <Constant.h>

namespace Mini
{
    class Tile
    {
    private:
        bool isDora    = false;
        bool isAkaDora = false;
    public:
        Tile();
        virtual ~Tile() = 0;

        // Setters
        void SetIsDora(const bool value);
        void SetIsAkaDora(const bool value);
        // Getters
        bool GetIsDora() const;
        bool GetIsAkaDora() const;
    };
    
    class CharacterTile : public Tile
    {
        private:
        public:
            CharacterTile();
            virtual ~CharacterTile() = 0;
    }

    class DragonTile : public CharacterTile
    {
        private:
            DragonType dragonType;
        public:
            DragonTile();
            virtual ~DragonTile();

            // Setters
            void SetType(const DragonType type);
            // Getters
            DragonType GetType() const;
    }

    class WindTile : public CharacterTile
    {
        private:
            WindType windType;
        public:
            WindTile();
            virtual ~WindTile();

            // Setters
            void SetType(const WindType type);
            // Getters
            WindType GetType() const;
    }

    class NumberTile : public Tile
    {
        private:
            NumberType numberType;
            uint8_t numberValue;
        public:
            NumberTile();
            virtual ~NumberTile();

            // Setters
            void SetType(const NumberType type);
            void SetNumber(const uint8_t value);
            // Getters
            NumberType GetType() const;
            uint8_t GetNumber() const;
    }
} // namespace Mini

#endif // __MINI_MAHJONG_TILE_H__
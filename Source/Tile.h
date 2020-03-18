#ifndef __MINI_MAHJONG_TILE_H__
#define __MINI_MAHJONG_TILE_H__

#include <Constant.h>

#include <string>

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
        virtual std::string ToString() const = 0;

        // Setters
        void SetIsDora(const bool value);

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
        virtual std::string ToString() const = 0;
    };

    class DragonTile : public CharacterTile
    {
    private:
        DragonType dragonType;
    public:
        DragonTile(DragonType type);
        virtual ~DragonTile();
        virtual std::string ToString() const;

        // Getters
        DragonType GetType() const;
    };

    class WindTile : public CharacterTile
    {
    private:
        WindType windType;
    public:
        WindTile(WindType type);
        virtual ~WindTile();
        virtual std::string ToString() const;

        // Getters
        WindType GetType() const;
    };

    class NumberTile : public Tile
    {
    private:
        NumberType numberType;
        uint8_t numberValue;
    public:
        NumberTile(NumberType type, const uint8_t value);
        virtual ~NumberTile();
        virtual std::string ToString() const;

        // Getters
        NumberType GetType() const;
        uint8_t GetNumber() const;
    };
} // namespace Mini

#endif // __MINI_MAHJONG_TILE_H__
#ifndef __MINI_MAHJONG_TILE_H__
#define __MINI_MAHJONG_TILE_H__

#include <Source/Constant.h>

#include <string>
#include <vector>

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
        virtual uint8_t GetIdentifier() const = 0;

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
        virtual uint8_t GetIdentifier() const = 0;
    };

    class DragonTile : public CharacterTile
    {
    private:
        DragonType dragonType;
    public:
        DragonTile(DragonType type);
        virtual ~DragonTile();
        virtual std::string ToString() const;
        virtual uint8_t GetIdentifier() const;

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
        virtual uint8_t GetIdentifier() const;

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
        virtual uint8_t GetIdentifier() const;

        // Getters
        NumberType GetType() const;
        uint8_t GetNumber() const;
    };

    // Some functions related with Tile class
    std::vector<Tile *> GetCompleteTileLists();

    const static std::vector<uint8_t> YaochuuTileIdList = { 
            DragonTile(DragonType::White).GetIdentifier(),
            DragonTile(DragonType::Green).GetIdentifier(),
            DragonTile(DragonType::Red).GetIdentifier(),
            WindTile(WindType::East).GetIdentifier(),
            WindTile(WindType::South).GetIdentifier(),
            WindTile(WindType::West).GetIdentifier(),
            WindTile(WindType::North).GetIdentifier(),
            NumberTile(NumberType::Cracks, 1).GetIdentifier(),
            NumberTile(NumberType::Cracks, 9).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 1).GetIdentifier(),
            NumberTile(NumberType::Bamboo, 9).GetIdentifier(),
            NumberTile(NumberType::Dots, 1).GetIdentifier(),
            NumberTile(NumberType::Dots, 9).GetIdentifier()
    };

    const static std::vector<uint8_t> RoutouTileIdList = {
        NumberTile(NumberType::Cracks, 1).GetIdentifier(),
        NumberTile(NumberType::Cracks, 9).GetIdentifier(),
        NumberTile(NumberType::Bamboo, 1).GetIdentifier(),
        NumberTile(NumberType::Bamboo, 9).GetIdentifier(),
        NumberTile(NumberType::Dots, 1).GetIdentifier(),
        NumberTile(NumberType::Dots, 9).GetIdentifier()
    };

    const static std::vector<uint8_t> JiTileIdList = {
        DragonTile(DragonType::White).GetIdentifier(),
        DragonTile(DragonType::Green).GetIdentifier(),
        DragonTile(DragonType::Red).GetIdentifier(),
        WindTile(WindType::East).GetIdentifier(),
        WindTile(WindType::South).GetIdentifier(),
        WindTile(WindType::West).GetIdentifier(),
        WindTile(WindType::North).GetIdentifier()
    };

} // namespace Mini

#endif // __MINI_MAHJONG_TILE_H__
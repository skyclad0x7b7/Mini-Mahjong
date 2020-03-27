#include <Source/Assert.h>
#include <Source/Tile.h>

namespace Mini
{
    // ==================================================
    // class Tile implementation
    // ==================================================
    Tile::Tile()
    {
        
    }

    Tile::~Tile()
    {

    }

    void Tile::SetIsDora(const bool value)
    {
        isDora = value;
    }

    bool Tile::GetIsDora() const
    {
        return isDora;
    }

    bool Tile::GetIsAkaDora() const
    {
        return isAkaDora;
    }

    // ==================================================
    // class CharacterTile implementation
    // ==================================================
    CharacterTile::CharacterTile()
    {

    }

    CharacterTile::~CharacterTile()
    {

    }


    // ==================================================
    // class DragonTile implementation
    // ==================================================
    DragonTile::DragonTile(DragonType type)
    {
        dragonType = type;
    }

    DragonTile::~DragonTile()
    {

    }

    std::string DragonTile::ToString() const
    {
        std::string ret;

        switch (dragonType)
        {
        case DragonType::White:
            ret = "白";
            break;
        case DragonType::Green:
            ret = "発";
            break;
        case DragonType::Red:
            ret = "中";
            break;
        default:
            assert_unreachable();
        }

        return ret;
    }

    uint8_t DragonTile::GetIdentifier() const
    {
        uint8_t identifier = 0x30;
        
        switch (dragonType)
        {
        case DragonType::White:
            identifier += 0x01;
            break;
        case DragonType::Green:
            identifier += 0x02;
            break;
        case DragonType::Red:
            identifier += 0x003;
            break;
        default:
            assert_unreachable();
        }

        return identifier;
    }

    DragonType DragonTile::GetType() const
    {
        return dragonType;
    }


    // ==================================================
    // class WindTile implementation
    // ==================================================
    WindTile::WindTile(WindType type)
    {
        windType = type;
    }

    WindTile::~WindTile()
    {

    }

    std::string WindTile::ToString() const
    {
        switch(windType)
        {
        case WindType::East:
            return "東";
            break;
        case WindType::South:
            return "南";
            break;
        case WindType::West:
            return "西";
            break;
        case WindType::North:
            return "北";
            break;
        default:
            assert_unreachable();
        }
    }

    uint8_t WindTile::GetIdentifier() const
    {
        uint8_t identifier = 0x40;
        
        switch (windType)
        {
        case WindType::East:
            identifier += 0x01;
            break;
        case WindType::South:
            identifier += 0x02;
            break;
        case WindType::West:
            identifier += 0x03;
            break;
        case WindType::North:
            identifier += 0x04;
            break;
        default:
            assert_unreachable();
        }

        return identifier;
    }

    WindType WindTile::GetType() const
    {
        return windType;
    }


    // ==================================================
    // class NumberTile implementation
    // ==================================================
    NumberTile::NumberTile(NumberType type, const uint8_t value)
    {
        numberType = type;

        debug_assert(value != 0, "number value can't be 0");
        debug_assert(value <= 9, "number value can't exceed 9");
        numberValue = value;
    }
    
    NumberTile::~NumberTile()
    {

    }

    std::string NumberTile::ToString() const
    {
        std::string ret = std::to_string(numberValue);

        switch(numberType)
        {
        case NumberType::Cracks:
            ret += "萬";
            break;
        case NumberType::Dots:
            ret += "筒";
            break;
        case NumberType::Bamboo:
            ret += "索";
            break;
        default:
            assert_unreachable();
        }

        return ret;
    }

    uint8_t NumberTile::GetIdentifier() const
    {
        uint8_t identifier = 0;
        
        switch (numberType)
        {
        case NumberType::Cracks:
            identifier = 0x00;
            break;
        case NumberType::Dots:
            identifier = 0x10;
            break;
        case NumberType::Bamboo:
            identifier = 0x20;
            break;
        default:
            assert_unreachable();
        }

        identifier += numberValue;
        return identifier;
    }

    NumberType NumberTile::GetType() const
    {
        return numberType;
    }

    uint8_t NumberTile::GetNumber() const
    {
        return numberValue;
    }

    // ==================================================
    // Some functions related with Tile class implementation
    // ==================================================
    std::vector<Tile *> GetCompleteTileLists()
    {
        std::vector<Tile *> ret;

        for (int i = 0; i < 4; ++i)
        {
            // Wind Tiles
            ret.emplace_back(new WindTile(WindType::East));
            ret.emplace_back(new WindTile(WindType::South));
            ret.emplace_back(new WindTile(WindType::West));
            ret.emplace_back(new WindTile(WindType::North));

            // Dragon Tiles
            ret.emplace_back(new DragonTile(DragonType::White));
            ret.emplace_back(new DragonTile(DragonType::Green));
            ret.emplace_back(new DragonTile(DragonType::Red));

            // Number Tiles
            for (int num = 1; num <= 9; ++num)
            {
                ret.emplace_back(new NumberTile(NumberType::Cracks, num));
                ret.emplace_back(new NumberTile(NumberType::Dots, num));
                ret.emplace_back(new NumberTile(NumberType::Bamboo, num));
            }
        }

        return ret;
    }

} // namespace Mini
#include <Tile.h>

namespace Mini
{
    // ==================================================
    // class Tile implements
    // ==================================================
    Tile::Tile()
    {
        
    }

    void Tile::SetIsDora(const bool value)
    {
        isDora = value;
    }

    void Tile::SetIsAkaDora(const bool value)
    {
        isAkaDora = value;
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
    // class CharacterTile implements
    // ==================================================
    CharacterTile::CharacterTile()
    {

    }


    // ==================================================
    // class DragonTile implements
    // ==================================================
    DragonTile::DragonTile()
    {

    }

    void DragonTile::SetType(const DragonType type)
    {
        dragonType = type;
    }

    DragonType DragonTile::GetType() const
    {
        return dragonType;
    }


    // ==================================================
    // class WindTile implements
    // ==================================================
    WindTile::WindTile()
    {

    }

    WindTile::SetType(const WindType type)
    {
        windType = type;
    }

    WindType WindTile::GetType() const
    {
        return windType;
    }


    // ==================================================
    // class NumberTile implements
    // ==================================================
    NumberTile::NumberTile()
    {

    }

    void NumberTile::SetType(const NumberType type)
    {
        numberType = type;
    }

    void NumberTile::SetNumber(const uint8_t value)
    {
        debug_assert(value != 0, "number value can't be 0");
        debug_assert(value  < 9, "number value can't exceed 9");
        numberValue = value;
    }

    NumberType NumberTile::GetType() const
    {
        return numberType;
    }

    uint8_t NumberTile::GetNumber() const
    {
        return numberValue;
    }


} // namespace Mini
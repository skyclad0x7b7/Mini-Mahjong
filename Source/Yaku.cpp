#include <Source/Yaku.h>

namespace Mini
{
    Yaku::Yaku(std::string argIdentifier, int argMenzenScore, int argScore, bool argShouldMenzen) : 
        identifier(argIdentifier), menzenScore(argMenzenScore), score(argScore), shouldMenzen(argShouldMenzen);
    {

    }

    // Getters
    std::string Yaku::GetIdentifier() const
    {
        return identifier;
    }

    int Yaku::GetMenzenScore() const
    {
        return menzenScore;
    }

    int Yaku::GetScore() const
    {
        return score;
    }

    bool Yaku::GetShouldMenzen() const
    {
        return shouldMenzen;
    }

    virtual bool CanWin(const std::vector<Tile*>& handTiles, const std::vector<Tile*>& droppedTiles, const std::vector<TileGroup*>& calledTileGroup, bool isRon)
    {
        // Common condition
        if (!isMenzen && GetScore() == 0)
        {
            return false;
        } 
    }


    /*
    *  Tangyao
    */
    virtual bool CanWin(const std::vector<Tile*>& handTiles, const std::vector<Tile*>& droppedTiles, const std::vector<TileGroup*>& calledTileGroup, bool isMenzen, bool isRon)
    {
        if (!Yaku::CanWin())
        {
            return false;
        }
        
        static std::vector<uint8_t> checkTileList = { 
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

        
        // Check if there are 1, 9, character tiles
        
    }


} // namespace Mini
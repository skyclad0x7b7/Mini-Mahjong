#include <assert.h>
#include "Tile.h"

namespace mahjong
{
	Tile::Tile(const TileType tileType, const int data , const bool isDora)
	{
		assert( 
			( (tileType == TileType::Manzu || tileType == TileType::Ponzu || tileType == TileType::Souzu) && 1 <= data && data <= 9) ||
			( tileType == TileType::Special && 1 <= data && data <= 7 )
		);
		m_data = tileType | data;
		m_isDora = isDora;
	}

	TileType Tile::getTileType() const
	{
		return static_cast<TileType>(m_data & 0b11000000);
	}

	int Tile::getTileNumber() const
	{
		return m_data & 0b00001111;
	}

	uint8_t Tile::getData() const
	{
		return m_data;
	}

	bool Tile::isDora() const
	{
		return m_isDora;
	}

	// Operator overloading
	bool Tile::operator==(const Tile& t) const
	{
		return m_data == t.getData();
	}

	bool Tile::operator!=(const Tile& t) const
	{
		return m_data != t.getData();
	}

	bool Tile::operator<(const Tile& t) const
	{
		return m_data < t.getData();
	}

	bool Tile::operator<=(const Tile& t) const
	{
		return m_data <= t.getData();
	}

	bool Tile::operator>(const Tile& t) const
	{
		return m_data > t.getData();
	}

	bool Tile::operator>=(const Tile& t) const
	{
		return m_data >= t.getData();
	}
}
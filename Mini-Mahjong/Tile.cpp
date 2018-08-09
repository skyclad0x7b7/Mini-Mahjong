#include <assert.h>
#include "Tile.h"

namespace mahjong
{
	Tile::Tile(const TileType tileType, const int data , const bool isDora)
	{
		assert(1 <= data && data <= 9);
		m_data = tileType | data;
		m_isDora = isDora;
	}

	TileType Tile::getTileType() const
	{
		return static_cast<TileType>(m_data & 0xFF000000);
	}

	uint8_t Tile::getData() const
	{
		return m_data;
	}

	bool Tile::isDora() const
	{
		return m_isDora;
	}
}
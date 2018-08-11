#include "Player.h"

namespace mahjong
{
	void Player::initialize(const int score, const Wind& wind)
	{
		m_score = score;
		m_wind = wind;
		m_hand.initialize();
	}

	Tile Player::pickTile(TileMountain* pTileMountain)
	{
		Tile ret = pTileMountain->pickTile();
		m_hand.putTile(ret);
		return ret;
	}

	const Tile Player::discardTileBefore(const size_t index)
	{
		return m_hand.discardTileBefore(index);
	}

	void Player::discardTileAfter(const Tile newTile)
	{
		m_hand.discardTileAfter(newTile);
	}

	bool Player::canClaim(const Tile& newTile, const Wind& wind) const
	{
		// Chi Check
		// TODO : Wind Check & Operator Overloading or find better way
	}
}
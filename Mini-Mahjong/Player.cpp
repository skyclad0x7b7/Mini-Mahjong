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
		bool canChi  = false;
		bool canPong = false;
		bool canKang = false;

		if ((m_wind - 1) == wind)
			canChi = m_hand.canChi(newTile);

		if((canKang = m_hand.canKang(newTile)) == false)
			canPong = m_hand.canPong(newTile);

		return canChi || canPong || canKang;
	}
}
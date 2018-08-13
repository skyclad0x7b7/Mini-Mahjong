#include "Player.h"

#include <iostream>

namespace mahjong
{
	void Player::initialize(const int score, const Wind& wind)
	{
		m_score = score;
		m_wind = wind;
	}

	Tile Player::pickTile(TileMountain* pTileMountain)
	{
		Tile ret = pTileMountain->pickTile();
		putTile(ret);
		return ret;
	}

	const mahjong::ClaimType Player::canClaim(const Tile& newTile, const Wind& wind) const
	{
		ClaimType ret = ClaimType::None;
		
		bool canChi  = false;
		bool canKang = false;
		bool canPong = false;

		if ((m_wind - 1) == wind)
			canChi = this->canChi(newTile);

		if((canKang = this->canKang(newTile)) == false)
			canPong = this->canPong(newTile);

		ret |= canChi ? ClaimType::Chi : ClaimType::None;
		ret |= canKang ? ClaimType::Kang : ClaimType::None;
		ret |= canPong ? ClaimType::Pong : ClaimType::None;
		
		return ret;
	}
}
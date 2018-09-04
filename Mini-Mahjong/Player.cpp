#include "Player.h"

#include <iostream>

namespace mahjong
{
	void Player::initialize(const int score, const Wind& wind)
	{
		m_score = score;
		m_wind = wind;
		
	}

	std::string Player::getPlayerName() const
	{
		return m_playerName;
	}

	void Player::setPlayerName(std::string newName)
	{
		m_playerName = newName;
	}

	Wind Player::getWind() const
	{
		return m_wind;
	}

	void Player::changeWind()
	{
		m_wind++;
	}

	void Player::changeWind(const Wind& wind)
	{
		m_wind = wind;
	}

	int Player::getScore() const
	{
		return m_score;
	}

	const ClaimType Player::canClaim(const Tile& newTile, const Wind& roundWind, bool isTsumo) const
	{
		ClaimType ret = ClaimType::None;
		
		bool canChi  = false;
		bool canKang = false;
		bool canPong = false;

		if ((m_wind - 1) == roundWind)
			canChi = this->canChi(newTile, isTsumo);

		if((canKang = this->canKang(newTile, isTsumo)) == false)
			canPong = this->canPong(newTile, isTsumo);

		ret |= canChi ? ClaimType::Chi : ClaimType::None;
		ret |= canKang ? ClaimType::Kang : ClaimType::None;
		ret |= canPong ? ClaimType::Pong : ClaimType::None;
		
		return ret;
	}
}
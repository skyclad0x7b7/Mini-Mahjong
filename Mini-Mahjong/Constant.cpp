#include "Constant.h"

namespace mahjong
{
	Wind operator++(Wind& wind)
	{
		wind = static_cast<Wind>((static_cast<int>(wind) + 1) % 4);
		return wind;
	}

	Wind operator+(const Wind& wind, const int i)
	{
		Wind ret = static_cast<Wind>((static_cast<int>(wind) + i) % 4);
		return ret;
	}

	Wind operator-(const Wind& wind, const int i)
	{
		Wind ret = static_cast<Wind>((static_cast<int>(wind) - (i % 4) + 4) % 4);
		return ret;
	}

	ClaimType operator&(const ClaimType& type1, const ClaimType& type2)
	{
		return static_cast<ClaimType>(static_cast<int>(type1) & static_cast<int>(type2));
	}

	ClaimType operator|(const ClaimType& type1, const ClaimType& type2)
	{
		return static_cast<ClaimType>(static_cast<int>(type1) | static_cast<int>(type2));
	}

	ClaimType& operator|=(ClaimType& type1, const ClaimType& type2)
	{
		ClaimType newType = static_cast<ClaimType>(static_cast<int>(type1) | static_cast<int>(type2));
		type1 = newType;
		return type1;
	}
}
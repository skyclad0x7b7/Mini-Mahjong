#ifndef Mini_Mahjong_EntireTile_H__
#define Mini_Mahjong_EntireTile_H__

#pragma once

#include <vector>

#include "Tile.h"

namespace mahjong
{
	/* [Singleton Class] Use TileMountain::GetInstance() */
	class TileMountain
	{
	public:
		static TileMountain* GetInstance();
		
		size_t getRestTilesCount() const;

		virtual void reset();
		virtual Tile pickTile();
	protected:
		static std::vector<Tile> m_entireTile;
	private:
		TileMountain();
		TileMountain(const TileMountain& other);
		~TileMountain();
	};
}

#endif
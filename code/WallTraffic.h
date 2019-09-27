//---------------------------------------------------------------------------

#ifndef WallTrafficH
#define WallTrafficH
#include "WState.h"
class Wall;
//---------------------------------------------------------------------------
class WallTraffic
{
	private:
		WState* _state;
	public:
		WallTraffic();
		void setState ( WState* );
		void Continuous(Wall&, const sf::Texture&);
		void Skipped(Wall&, const sf::Texture&);
		void Tile(Wall&, const sf::Texture&);
};
#endif

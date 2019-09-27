//---------------------------------------------------------------------------

#ifndef WTransparentH
#define WTransparentH
#include <iostream>
#include <stdio.h>
#include "WState.h"
#include "WallTraffic.h"
//---------------------------------------------------------------------------

class WTransparent: public WState
{
	private:
		WallTraffic* _context;

	public:
		WTransparent(WallTraffic*);
		void Continuous(Wall&, const sf::Texture&);
};
#endif

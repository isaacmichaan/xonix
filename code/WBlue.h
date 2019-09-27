//---------------------------------------------------------------------------

#ifndef WBlueH
#define WBlueH
#include <iostream>
#include <stdio.h>
#include "WState.h"
#include "WallTraffic.h"
//---------------------------------------------------------------------------
class WBlue: public WState
{
	private:
		WallTraffic* _context;

	public:
		WBlue(WallTraffic*);
		void Continuous(Wall&, const sf::Texture&);
};
#endif

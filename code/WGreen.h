//---------------------------------------------------------------------------

#ifndef WGreenH
#define WGreenH
#include <iostream>
#include <stdio.h>
#include "WState.h"
#include "WallTraffic.h"
//---------------------------------------------------------------------------

class WGreen: public WState
{
	private:
		WallTraffic* _context;

	public:
		WGreen(WallTraffic*);
		void Continuous(Wall&, const sf::Texture&);
		void Skipped(Wall&, const sf::Texture&);
		virtual void Tile(Wall&, const sf::Texture&);
};

#endif

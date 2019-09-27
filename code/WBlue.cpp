//---------------------------------------------------------------------------


#pragma hdrstop   

#include "WBlue.h"
#include "WTransparent.h"
#include "Wall.h"
//---------------------------------------------------------------------------
WBlue::WBlue(WallTraffic* context): _context(context) {};

void WBlue::Continuous(Wall& w, const sf::Texture& texture)
{
	//printf("Blue Wall\n");
	w.setChar('b');
	w.setSpriteTexture(texture);
	_context->setState( new WTransparent(_context) );
}
#pragma package(smart_init)

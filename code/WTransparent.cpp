//---------------------------------------------------------------------------


#pragma hdrstop

#include "WTransparent.h"
#include "WGreen.h"
#include "WBlue.h"
#include "Wall.h"
//---------------------------------------------------------------------------
WTransparent::WTransparent(WallTraffic* context): _context(context) {};

void WTransparent::Continuous(Wall& w, const sf::Texture& texture)
{
	//printf("Transparent Wall\n");
	w.setChar('t');
	w.setSpriteTexture(texture);
	_context->setState( new WGreen(_context) );
}
#pragma package(smart_init)

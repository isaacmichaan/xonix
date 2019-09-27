//---------------------------------------------------------------------------


#pragma hdrstop

#include "WGreen.h"
#include "WBlue.h"
#include "WTransparent.h"
#include "Wall.h"
//---------------------------------------------------------------------------
WGreen::WGreen(WallTraffic* context): _context(context) {};

void WGreen::Continuous(Wall& w, const sf::Texture& texture)
{
	//printf("Green Wall\n");
	w.setChar('g');
	w.setSpriteTexture(texture);
	_context->setState( new WBlue(_context) );
}

void WGreen::Skipped(Wall& w, const sf::Texture& texture)
{
	//printf("Blue Wall\n");
	w.setChar('b');
	w.setSpriteTexture(texture);
	_context->setState(new WTransparent(_context));
}

void WGreen::Tile(Wall& w, const sf::Texture& texture)
{
	//printf("Orange Wall\n");
	w.setChar('o');
	w.setSpriteTexture(texture);
	_context->setState(new WTransparent(_context));
}
#pragma package(smart_init)

//---------------------------------------------------------------------------


#pragma hdrstop
#include <SFML/Graphics.hpp>
#include "WallTraffic.h"
#include "WTransparent.h"
#include "Wall.h"
//---------------------------------------------------------------------------

WallTraffic::WallTraffic()
{
	_state = new WTransparent(this);
}

void WallTraffic::setState ( WState* state )
{
	_state = state;
}

void WallTraffic::Continuous(Wall& w, const sf::Texture& texture)
{
	_state->Continuous(w, texture);
}

void WallTraffic::Skipped(Wall& w, const sf::Texture& texture)
{
	_state->Skipped(w, texture);
}

void WallTraffic::Tile(Wall& w, const sf::Texture& texture)
{
	_state->Tile(w, texture);
}
#pragma package(smart_init)

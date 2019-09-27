#include "Wall.h"



//Wall::Wall()
//{
//}


Wall::~Wall()
{
}

void Wall::Handle(const sf::Texture& texture, char c)
{
	if (c == 'c')
		w_traffic.Continuous(*this, texture);
	
	if (c == 's')
		w_traffic.Skipped(*this, texture);
	
	if (c == 'o')
		w_traffic.Tile(*this, texture);
}

void Wall::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}

#pragma once
#include "StaticObject.h"
#include "WallTraffic.h"

class Wall : public StaticObject
{
private:
	WallTraffic w_traffic;
public:
	using StaticObject::StaticObject;
	~Wall();
	void Handle(const sf::Texture&, char);
	virtual void draw(sf::RenderWindow&) const;
};

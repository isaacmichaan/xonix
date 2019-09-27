#include "ConquerBall.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"


//ConquerBall::ConquerBall()
//{
//}

ConquerBall::~ConquerBall()
{
}

void ConquerBall::move(const dynamicO& movable_object, const staticO& static_object)
{
	static float x = 0, y = 0;
	keyboard(x, y);
	setPos(getSprite().getPosition().x + x, getSprite().getPosition().y + y);
	collision(movable_object, static_object);
	setSpritePos(sf::Vector2f(m_x, m_y));
}

void ConquerBall::keyboard(float& x, float& y) const
{
	int i = rand() % 4;
	if (i == 0) 
	{ 
		x = -getTileSize(); 
		y = 0; 
	};
	
	if (i == 1) 
	{ 
		x = getTileSize(); 
		y = 0; 
	};
	
	if (i == 2) 
	{ 
		x = 0; 
		y = -getTileSize(); 
	};
	
	if (i == 3) 
	{ 
		x = 0; 
		y = getTileSize(); 
	};
}

void ConquerBall::setPos(const float& x, const float& y)
{
	m_x = x; 
	m_y = y;
}

void ConquerBall::collision(const dynamicO& movable_object, const staticO& static_object)
{
	setLife(false);
	setBuildTile(false);
	for_each_pair(this, movable_object, static_object, [this](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});
}

bool ConquerBall::collide(GameObject &, GameObject & object2) const
{
	return (sf::Vector2f(m_x, m_y) == object2.getSpritePos());
}

void ConquerBall::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}
#include "SimpleBall.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"
#include "User.h"
class Board;



//SimpleBall::SimpleBall()
//{
//}


SimpleBall::~SimpleBall()
{
}

void SimpleBall::move(const dynamicO& movable_object, const staticO& static_object)
{
	float x = 0, y = 0;
	keyboard(x, y, movable_object, static_object);
	setPos(getSprite().getPosition().x + x, getSprite().getPosition().y + y);
	collision(movable_object, static_object);
	setSpritePos(sf::Vector2f(m_x, m_y));
}

void SimpleBall::setPos(const float& x, const float& y)
{
	m_x = x; 
	m_y = y;
}

void SimpleBall::collision(const dynamicO& movable_object, const staticO& static_object)
{
	setLife(false);
	for_each_pair(this, movable_object, static_object, [this](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});
}

bool SimpleBall::collide(GameObject &, GameObject & object2) const
{
	int x, y;
	
	if (object2.getSpritePos().x > m_x) 
	{
		x = object2.getSpritePos().x - m_x;
		y = object2.getSpritePos().y - m_y;
	}
	
	else 
	{
		x = m_x - object2.getSpritePos().x;
		y = m_y - object2.getSpritePos().y;
	}

	return (x >= 0 && x <= 18 && y >= 0 && y <= 18);
}

void SimpleBall::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}
#include "DestroyerBall.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"

//DestroyerBall::DestroyerBall()
//{
//}


DestroyerBall::~DestroyerBall()
{
}

void DestroyerBall::move(const dynamicO& movable_object, const staticO& static_object)
{
	float x = 0, y = 0;
	keyboard(x, y);
	setPos(getSprite().getPosition().x + x, getSprite().getPosition().y + y);
	collision(movable_object, static_object);
	setSpritePos(sf::Vector2f(m_x, m_y));
}

void DestroyerBall::keyboard(float& x, float& y) const
{
	int i = rand() % 4;
	if (i == 0) x += rand() % 2;
	if (i == 1) x -= rand() % 2;
	if (i == 2) y += rand() % 2;
	if (i == 3) y -= rand() % 2;

	//transform to 18 pixels
	x *= getTileSize();
	y *= getTileSize();
}

void DestroyerBall::setPos(const float& x, const float& y)
{
	m_x = x; 
	m_y = y;
}

void DestroyerBall::collision(const dynamicO& movable_object, const staticO& static_object)
{
	setLife(false);
	setDestroyTile(false);
	for_each_pair(this, movable_object, static_object, [this](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});
}

bool DestroyerBall::collide(GameObject &, GameObject & object2) const
{
	return (sf::Vector2f(m_x, m_y) == object2.getSpritePos());
}

void DestroyerBall::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}
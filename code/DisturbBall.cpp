#include "DisturbBall.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"


//DisturbBall::DisturbBall()
//{
//}

DisturbBall::~DisturbBall()
{
}

void DisturbBall::move(const dynamicO& movable_object, const staticO& static_object)
{
	/*static*/ float x = 0, y = 0;
	keyboard(x, y, movable_object);
	m_old_x = m_x;
	m_old_y = m_y;
	setPos(getSprite().getPosition().x + x, getSprite().getPosition().y + y);
	collision(movable_object, static_object);
	setSpritePos(sf::Vector2f(m_x, m_y));
}

void DisturbBall::keyboard(float& x, float& y, const dynamicO& movable_object) const
{
	static int i = rand() % 4;
	if (m_old_x == m_x && m_old_y == m_y) 
	 i = rand() % 4;
	

	if ((movable_object[0]->getSprite().getPosition().x >= m_x) && (movable_object[0]->getSprite().getPosition().y <= m_y)) //(i==0)
	{

	//right
		x = getTileSize();
		y = 0;
	};

	if ((movable_object[0]->getSprite().getPosition().x <= m_x) && (movable_object[0]->getSprite().getPosition().y >= m_y)) //(i==1)
	{
		////left
		x = -getTileSize();
		y = 0;
	};

	if ((movable_object[0]->getSprite().getPosition().x >= m_x) && (movable_object[0]->getSprite().getPosition().y >= m_y)) //(i==2)
	{
		//doun
		x = 0;
		y = getTileSize();
	};

	if ((movable_object[0]->getSprite().getPosition().x <= m_x) && (movable_object[0]->getSprite().getPosition().y <= m_y)) //(i==3)
	{
		//up
		x = 0;
		y = -getTileSize();
	};
}

void DisturbBall::setPos(const float& x, const float& y)
{
	m_x = x; 
	m_y = y;
}

void DisturbBall::collision(const dynamicO& movable_object, const staticO& static_object)
{
	setLife(false);
	for_each_pair(this, movable_object, static_object, [this](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});
	checkBorders();
}

bool DisturbBall::collide(GameObject &, GameObject & object2) const
{
	return (sf::Vector2f(m_x, m_y) == object2.getSpritePos());
}

void DisturbBall::checkBorders()
{
	if (m_x < 0) m_x = 0; 
	if (m_x > 1512 - 1) m_x = 1512 - getTileSize(); // sf::Videomovable_objectde(1512, 702)
	if (m_y < 0) m_y = 0; 
	if (m_y > 702 - 1) m_y = 702 - getTileSize(); // sf::Videomovable_objectde(1512, 702)
}

void DisturbBall::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}
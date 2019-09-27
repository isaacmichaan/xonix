#include "User.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"


//User::User()
//{
//}

User::~User()
{
}

void User::move(const dynamicO& movable_object, const staticO& static_object)
{
	static float x = 0, y = 0;
	if (stop)
	{
		x = 0;
		y = 0;
		stop = false;
	}
	keyboard(x, y);
	setPos(getSprite().getPosition().x + x, getSprite().getPosition().y + y);
	collision(movable_object, static_object);
	setSpritePos(sf::Vector2f(m_x, m_y));
}

void User::keyboard(float& x, float& y) const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { x = -getTileSize(); y = 0; };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { x = getTileSize(); y = 0; };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { x = 0; y = -getTileSize(); };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { x = 0; y = getTileSize(); };
}

void User::setPos(const float& x, const float& y)
{
	m_x = x; 
	m_y = y;
}

void User::collision(const dynamicO& movable_object, const staticO& static_object)
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

bool User::collide(GameObject &, GameObject & object2) const
{
	return (sf::Vector2f(m_x, m_y) == object2.getSpritePos());
}

void User::checkBorders()
{
	if (m_x < 0) m_x = 0; 
	if (m_x > 1512 - 1) m_x = 1512 - getTileSize(); // sf::Videomode(1512, 702)
	if (m_y < 0) m_y = 0; 
	if (m_y > 702 - 1) m_y = 702 - getTileSize(); // sf::Videomode(1512, 702)
}

void User::stopUser()
{
	stop = true;
}

void User::draw(sf::RenderWindow & window) const
{
	window.draw(getSprite());
}
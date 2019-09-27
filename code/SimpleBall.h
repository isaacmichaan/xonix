#pragma once
#include "Ball.h"

class SimpleBall : public Ball
{
protected:
	float m_x; // hold sprite.x new position
	float m_y; // hold sprite.y new position
	float ballAngle = 100.f; // to be changed later
public:
	using Ball::Ball;
	virtual ~SimpleBall();
	virtual void move(const dynamicO&, const staticO&);
	virtual void keyboard(float& x, float& y, const dynamicO&, const staticO&) const = 0;
	void setPos(const float&, const float&);
	void collision(const dynamicO&, const staticO&);
	virtual bool collide(GameObject&, GameObject&) const;
	virtual void draw(sf::RenderWindow&) const;
};


#pragma once
#include "Ball.h"

class DestroyerBall : public Ball
{
private:
	float m_x; // hold sprite.x new position
	float m_y; // hold sprite.y new position
public:
	using Ball::Ball;
	~DestroyerBall();
	virtual void move(const dynamicO&, const staticO&);
	void keyboard(float&, float&) const;
	void setPos(const float&, const float&);
	void collision(const dynamicO&, const staticO&);
	virtual bool collide(GameObject&, GameObject&) const;
	virtual void draw(sf::RenderWindow&) const;
};


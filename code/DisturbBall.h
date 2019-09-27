#pragma once
#include "Ball.h"


class DisturbBall : public Ball
{
private:
	float m_x; // hold sprite.x new position
	float m_y; // hold sprite.y new position
	float m_old_x = 0;
	float m_old_y = 0;
public:
	using Ball::Ball;
	~DisturbBall();
	virtual void move(const dynamicO&, const staticO&);
	void keyboard(float&, float&, const dynamicO& movable_object) const;
	void setPos(const float&, const float&);
	void collision(const dynamicO&, const staticO&);
	virtual bool collide(GameObject&, GameObject&) const;
	void checkBorders();
	virtual void draw(sf::RenderWindow&) const;
};
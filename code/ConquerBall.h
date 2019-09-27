#pragma once
#include "Conqueror.h"


class ConquerBall : public Conqueror
{
private:
	float m_x; // hold sprite.x new position
	float m_y; // hold sprite.y new position
public:
	using Conqueror::Conqueror;
	~ConquerBall();
	virtual void move(const dynamicO&, const staticO&);
	void keyboard(float&, float&) const;
	void setPos(const float&, const float&);
	void collision(const dynamicO&, const staticO&);
	virtual bool collide(GameObject&, GameObject&) const;
	virtual void draw(sf::RenderWindow&) const;
};
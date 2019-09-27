#pragma once
#include "Conqueror.h"


class User : public Conqueror
{
private:
	float m_x; // hold sprite.x new position
	float m_y; // hold sprite.y new position
	bool stop = false;
public:
	using Conqueror::Conqueror;
	~User();
	virtual void move(const dynamicO&, const staticO&);
	void keyboard(float&, float&) const;
	void setPos(const float&, const float&);
	void collision(const dynamicO&, const staticO&);
	virtual bool collide(GameObject&, GameObject&) const;
	void checkBorders();
	void stopUser();
	virtual void draw(sf::RenderWindow&) const;
};
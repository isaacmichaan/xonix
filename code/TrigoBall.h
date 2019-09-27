#pragma once
#include "SimpleBall.h"

class TrigoBall : public SimpleBall
{
private:
	int m_diraction;
public:
	TrigoBall(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos, char color);
	~TrigoBall();
	void keyboard(float& x, float& y, const dynamicO&, const staticO&) const;
	void setDiraction(int diraction);
	int getDiraction();
};


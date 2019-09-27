#pragma once
#include "SimpleBall.h"

class ChaserBall : public SimpleBall
{
public:
	ChaserBall(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos, char color);
	~ChaserBall();
	void keyboard(float& x, float& y, const dynamicO&, const staticO&) const;
};


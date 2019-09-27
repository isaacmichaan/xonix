#include "ChaserBall.h"


ChaserBall::ChaserBall(const sf::Texture & texture, const sf::Vector2f & size, const sf::Vector2f & pos, char color) : SimpleBall(texture, size, pos, color)
{

}


ChaserBall::~ChaserBall()
{

}


void ChaserBall::keyboard(float& x, float& y, const dynamicO& movable_object, const staticO& static_object) const
{
	float factor = 50 * getTimer();
	
	//���� ����� ������ �����
	if ((movable_object[0]->getSprite().getPosition().x > m_x) && (movable_object[0]->getSprite().getPosition().y < m_y))
	{
		////up rghit
		x = std::cos(ballAngle) * factor;
		y = std::sin(ballAngle) * factor;
	}

	//���� ���� ����� ������ ����
	if ((movable_object[0]->getSprite().getPosition().x <= m_x) && (movable_object[0]->getSprite().getPosition().y >= m_y))
	{
		//doun left
		x = std::cos(ballAngle) * -factor;
		y = std::sin(ballAngle) * -factor;
	}

	if ((movable_object[0]->getSprite().getPosition().x > m_x) && (movable_object[0]->getSprite().getPosition().y > m_y))
	{
		//���� ���� �����
		x = std::sin(ballAngle) * -factor;
		y = std::cos(ballAngle) * factor;
	}

	if ((movable_object[0]->getSprite().getPosition().x <= m_x) && (movable_object[0]->getSprite().getPosition().y <= m_y))
	{
		//���� ����� �����
		x = std::sin(ballAngle) * factor;
		y = std::cos(ballAngle) * -factor;
	}
}

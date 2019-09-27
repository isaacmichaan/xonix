#include "TrigoBall.h"



TrigoBall::TrigoBall(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos, char color) :SimpleBall (texture, size, pos, color) 
{
	int i = 0;
	srand(2);
	m_diraction = rand() % 4;	
}


TrigoBall::~TrigoBall()
{
}

void TrigoBall::keyboard(float & x, float & y, const dynamicO &, const staticO &) const
{
	float factor = 50 * getTimer();

	switch (m_diraction)
	{
	case 0:
	////up rghit
		x = std::cos(ballAngle) * factor;
		y = std::sin(ballAngle) * factor;
		break;

	case 1:
		//יורד למטה ימינה
		x = std::sin(ballAngle) * -factor;
		y = std::cos(ballAngle) * factor;
		break;
		
	case 2:
		//doun left
		x = std::cos(ballAngle) * -factor;
		y = std::sin(ballAngle) * -factor;
		break;
		
	case 3:
		//עולה למעלה שמאלה
		x = std::sin(ballAngle) * factor;
		y = std::cos(ballAngle) * -factor;
		break;
	}

}

void TrigoBall::setDiraction(int diraction)
{
	m_diraction = diraction;
}

int TrigoBall::getDiraction()
{
	return m_diraction;
}

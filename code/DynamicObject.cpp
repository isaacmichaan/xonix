#include "DynamicObject.h"



//DynamicObject::DynamicObject()
//{
//}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::setTimer(const float& time)
{
	if (time > 0)
		m_timer += time;
	else m_timer = time;
}

float DynamicObject::getTimer() const
{
	return m_timer;
}

void DynamicObject::setDelay(const float& delay)
{
	m_delay = delay;
}

float DynamicObject::getDelay() const
{
	return m_delay;
}

bool DynamicObject::getLife() const
{
	return m_life;
}

void DynamicObject::setLife(const bool& b)
{
	m_life = b;
}

void DynamicObject::setDestroyTile(const bool& b)
{
	m_destroy_tile = b;
}

bool DynamicObject::getDestroyTile() const
{
	return m_destroy_tile;
}

void DynamicObject::setBuildTile(const bool& b)
{
	m_build_tile = b;
}

bool DynamicObject::getBuildTile() const
{
	return m_build_tile;
}
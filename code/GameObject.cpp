#include "GameObject.h"



GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos, char color) : m_color(color)
{
	setSpriteTexture(texture);
	setSpritePos(pos);
}


GameObject::~GameObject()
{
}

sf::Sprite GameObject::getSprite() const
{
	return m_sprite;
}

void GameObject::setSpritePos(const sf::Vector2f & pos)
{
	m_sprite.setPosition(pos);
}

sf::Vector2f GameObject::getSpritePos() const
{
	return m_sprite.getPosition();
}

const float GameObject::getTileSize() const
{
	return m_tile_size;
}

void GameObject::setChar(const char& c)
{
	m_color = c;
}

char GameObject::getChar() const
{
	return m_color;
}

void GameObject::setSpriteTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}
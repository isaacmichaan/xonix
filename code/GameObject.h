#pragma once
#include <SFML/Graphics.hpp>
class DynamicObject;
class StaticObject;
typedef std::vector<std::unique_ptr<DynamicObject>> dynamicO;
typedef std::vector<std::vector<std::unique_ptr<StaticObject>>> staticO;

class GameObject
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	const float m_tile_size = 18; // If Changed, need to do the same on Board and Controller
	char m_color;
public:
	GameObject(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, char);
	~GameObject();
	sf::Sprite getSprite() const;
	void setSpritePos(const sf::Vector2f&);
	sf::Vector2f getSpritePos() const;
	const float getTileSize() const;
	void setChar(const char&);
	char getChar() const;
	void setSpriteTexture(const sf::Texture&);
	virtual void draw(sf::RenderWindow&) const = 0;
};


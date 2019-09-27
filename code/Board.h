#pragma once
#include <SFML/Graphics.hpp>
class DynamicObject;
class StaticObject;
typedef std::vector<std::unique_ptr<DynamicObject>> dynamicO;
typedef std::vector<std::vector<std::unique_ptr<StaticObject>>> staticO;

struct Point
{
	int x;
	int y;
};

class Board
{
private:
	sf::Texture m_texture_red;
	sf::Texture m_texture_purple;
	sf::Texture m_texture_blue;
	sf::Texture m_texture_green_wall;
	sf::Texture m_texture_green;
	sf::Texture m_texture_yellow;
	sf::Texture m_texture_light_blue;
	sf::Texture m_texture_orange;
	sf::Texture m_texture_transparent;
	const int m_tile_size = 18; // If Changed, need to do the same on GameObject and Controller
	sf::Vector2f m_up_left, m_down_left, m_up_right, m_down_right; // front and back of static_object vec
public:
	Board();
	~Board();
	void build(const std::string&, dynamicO&, staticO&);
	void newTile(const std::unique_ptr<DynamicObject>&, staticO&) const;
	void drop(const std::unique_ptr<DynamicObject>&, staticO&, const int&, const int&) const;
	void fillBoard(const std::unique_ptr<DynamicObject>&, staticO&) const;
	void getGreenToBlue(const std::unique_ptr<DynamicObject>&, staticO&) const;
	void destroyTile(const std::unique_ptr<DynamicObject>&, staticO&) const;
	void buildTile(const std::unique_ptr<DynamicObject>&, staticO&) const;
	void restart(const std::string&, dynamicO&, staticO&);
};


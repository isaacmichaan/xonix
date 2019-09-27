#pragma once
#include <SFML/Graphics.hpp>
class StaticObject;
typedef std::vector<std::vector<std::unique_ptr<StaticObject>>> staticO;

class InfoBar
{
private:
	int m_level;
	int m_life;
	int m_score;
	int m_percentage;
	sf::Time m_timeLimit;
	sf::Clock m_clock;
	sf::Font m_font;
public:
	InfoBar();
	void setNewLevel();
	void setLevel(int);
	int getLevel() const;
	void setLife(int);
	int getLife() const;
	void setScore(const staticO&, const int &);
	int getScore() const;
	void draw(sf::RenderWindow&);
	~InfoBar();
};
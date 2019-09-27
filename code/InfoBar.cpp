#include "InfoBar.h"
#include <sstream>
#include "StaticObject.h"

//===========================================
// c-tor . gets position and size
//===========================================
InfoBar::InfoBar() : m_level(1), m_life(3), m_score(0)
{
	m_font.loadFromFile("fonts/ARLRDBD.TTF");
}


//==================================================================
// set new level. 
// gets level, bomb limit, time limit (seconds as int), life to add.
//==================================================================
void InfoBar::setNewLevel()
{
	m_timeLimit = sf::seconds(float(240)); // 4 minutes
	m_clock.restart();
}


void InfoBar::setLevel(int level)
{
	m_level = level;
}


int InfoBar::getLevel() const
{
	return m_level;
}

void InfoBar::setLife(int life)
{
	m_life += life;
}

int InfoBar::getLife() const
{
	return m_life;
}

void InfoBar::setScore(const staticO& m_static_object, const int & total)
{
	int count = 0;
	for (const auto& so : m_static_object)
		for (int i = 0; i < so.size(); i++)
			if (so[i]->getChar() == 'b')
				count++;
	m_score = count;
	m_percentage = ((m_score * 100 / total) * 2); // it is multiplie by 2 because 50% is like 100% if we want 75% so it is multiplie by 3/4
}

int InfoBar::getScore() const
{
	return m_score;
}


//===========================================
// draw 
//===========================================
void InfoBar::draw(sf::RenderWindow & window)
{
	if (m_clock.getElapsedTime().asSeconds() >= m_timeLimit.asSeconds())
		m_clock.restart();

	int tsec = abs(m_timeLimit.asSeconds() - m_clock.getElapsedTime().asSeconds());
	int m_minute = tsec / 60;
	int m_sec = tsec % 60;

	std::string minute = (m_minute < 10) ? "0" + std::to_string(m_minute) : std::to_string(m_minute);
	std::string sec = (m_sec < 10) ? "0" + std::to_string(m_sec) : std::to_string(m_sec);
	std::string timePrint = "	Time: " + minute + ": " + sec;
	std::stringstream strToPrint; 
	strToPrint << "Level: " << m_level << timePrint << '\n' << "Life: " << m_life << "	Percentage: " << m_percentage << "%";
	
	sf::Text infoBar(strToPrint.str(), m_font, 25);
	infoBar.setPosition(sf::Vector2f{ 25, 615 });
	infoBar.setCharacterSize(27);
	infoBar.setFillColor(sf::Color::Black);
	window.draw(infoBar);
}


//===========================================
// d-tor
//===========================================
InfoBar::~InfoBar()
{
}

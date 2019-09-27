#include "Board.h"
#include <fstream>
#include <iostream>
#include "DynamicObject.h"
#include "StaticObject.h"
#include "User.h"
#include "ConquerBall.h"
#include "SimpleBall.h"
#include "ChaserBall.h"
#include "TrigoBall.h"
#include "DestroyerBall.h"
#include "DisturbBall.h"
#include "Wall.h"


Board::Board()
{
	m_texture_red.loadFromFile("images/tiles.png", sf::IntRect(36, 0, m_tile_size, m_tile_size));
	m_texture_purple.loadFromFile("images/purple.png", sf::IntRect(0, 0, m_tile_size, m_tile_size)); // 18, 0
	m_texture_blue.loadFromFile("images/tiles.png", sf::IntRect(0, 0, m_tile_size, m_tile_size));
	m_texture_green_wall.loadFromFile("images/tiles.png", sf::IntRect(54, 0, m_tile_size, m_tile_size)); // grenn wall
	m_texture_green.loadFromFile("images/green.png", sf::IntRect(0, 0, m_tile_size, m_tile_size)); // green ball
	m_texture_yellow.loadFromFile("images/yellow.png", sf::IntRect(0, 0, m_tile_size, m_tile_size)); // 72, 0
	m_texture_light_blue.loadFromFile("images/tiles.png", sf::IntRect(90, 0, m_tile_size, m_tile_size));
	m_texture_orange.loadFromFile("images/orange.png", sf::IntRect(0, 0, m_tile_size, m_tile_size)); // 108, 0
	m_texture_transparent.create(m_tile_size, m_tile_size);
}


Board::~Board()
{
}


//Build movable_object and static_object
void Board::build(const std::string & str, dynamicO & movable_object, staticO & static_object)
{
	std::ifstream file(str);
	
	// resize static_object vector
	int line;
	file.exceptions(file.failbit | file.badbit);
	try {
		file >> line;
	}
	catch (std::exception e) 
	{
			std::cout << e.what();
			exit(0);
	}
	static_object.resize(line);

	// build movable_object and static_object vector
	file.exceptions(file.badbit); // turn off failbit
	file.ignore(); // skip '/n'
	
	std::srand(std::time(0));
	int r = 0;
	char c;
	float x = 0, y = 0;
	int i = 0, j = 0;
	std::vector<Point> border;

	while (file)
	{
		if (file >> std::noskipws >> c) // otherwise last character on file will be read twice
		switch (c)
		{
		case '/':
			movable_object.push_back(std::make_unique < User >(m_texture_red, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'r'));
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		case '$':
			movable_object.push_back(std::make_unique < ConquerBall >(m_texture_orange, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'l'));
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		case '!':
			if ((std::rand()) % 2 == 0)
			{
				
				movable_object.push_back(std::make_unique < ChaserBall >(m_texture_purple, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'p'));
			}
			else
			{
				movable_object.push_back(std::make_unique < TrigoBall >(m_texture_purple, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'p'));
			}
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		case '%':
			movable_object.push_back(std::make_unique < DestroyerBall >(m_texture_yellow, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'y'));
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		case '@':
			movable_object.push_back(std::make_unique < DisturbBall >(m_texture_green, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'a')); // prefered to be changed
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		case '#':
			static_object[i].push_back(std::make_unique < Wall >(m_texture_blue, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 'b'));
			border.push_back({ i,j });
			break;
		case ' ':
			static_object[i].push_back(std::make_unique < Wall >(m_texture_transparent, sf::Vector2f(m_tile_size, m_tile_size), sf::Vector2f(x, y), 't'));
			break;
		default:
			break;
		}

		x += m_tile_size;
		j++;

		if (c == '\n')
		{
			y += m_tile_size;
			x = 0;
			i++;
			j = 0;
		}
	}
	file.close();

	// save board borders
	m_up_left = { static_object[border.front().x][border.front().y]->getSpritePos() };
	m_down_left = { static_object[border.back().x][border.front().y]->getSpritePos() };
	m_up_right = { static_object[border.front().x][border.back().y]->getSpritePos() };
	m_down_right = { static_object[border.back().x][border.back().y]->getSpritePos() };

	// initiate State and change outside border to '0'
	for (int i = 0; i < static_object.size(); i++)
	{
		for (int j = 0; j < static_object[i].size(); j++)
		{
			if (!(j > (m_up_left.x / m_tile_size) && i > (m_up_left.y / m_tile_size) && j > (m_down_left.x / m_tile_size) && i < (m_down_left.y / m_tile_size)
				&& j < (m_up_right.x / m_tile_size) && i >(m_up_right.y / m_tile_size) && j < (m_down_right.x / m_tile_size) && i < (m_down_right.y / m_tile_size)) && static_object[i][j]->getChar() != 'b')
			{
				static_object[i][j]->setChar('0');
			}
			else if (!(j > (m_up_left.x / m_tile_size) && i > (m_up_left.y / m_tile_size) && j > (m_down_left.x / m_tile_size) && i < (m_down_left.y / m_tile_size)
				&& j < (m_up_right.x / m_tile_size) && i >(m_up_right.y / m_tile_size) && j < (m_down_right.x / m_tile_size) && i < (m_down_right.y / m_tile_size)) && static_object[i][j]->getChar() == 'b')
			{
				static_object[i][j]->setChar('2');
			}
			else if (static_object[i][j]->getChar() == 't')
			{
				Wall& wall = dynamic_cast<Wall&>(*static_object[i][j]);
				wall.Handle(m_texture_transparent, 'c');
			}
		}
	}
}


void Board::newTile(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object) const
{	
	if (movable_object->getSpritePos().x > m_up_left.x && movable_object->getSpritePos().y > m_up_left.y && movable_object->getSpritePos().x > m_down_left.x  && movable_object->getSpritePos().y < m_down_left.y
		&& movable_object->getSpritePos().x < m_up_right.x && movable_object->getSpritePos().y > m_up_right.y && movable_object->getSpritePos().x < m_down_right.x && movable_object->getSpritePos().y < m_down_right.y)
	{
		if (static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]->getChar() == 't') ////////////
		{
			Wall& wall = dynamic_cast<Wall&>(*static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]);
			wall.Handle(m_texture_green_wall, 'c');
		}
	}
}


void Board::drop(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object, const int& y, const int& x) const
{ 
	if (!(movable_object->getSpritePos().x > m_up_left.x && movable_object->getSpritePos().y > m_up_left.y && movable_object->getSpritePos().x > m_down_left.x  && movable_object->getSpritePos().y < m_down_left.y
		&& movable_object->getSpritePos().x < m_up_right.x && movable_object->getSpritePos().y > m_up_right.y && movable_object->getSpritePos().x < m_down_right.x && movable_object->getSpritePos().y < m_down_right.y)
		|| static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]->getChar() == 'b')
	{
		if (static_object[y][x]->getChar() == 't') static_object[y][x]->setChar('1');
		if (static_object[y - 1][x]->getChar() == 't') drop(movable_object, static_object, y - 1, x);
		if (static_object[y + 1][x]->getChar() == 't') drop(movable_object, static_object, y + 1, x);
		if (static_object[y][x - 1]->getChar() == 't') drop(movable_object, static_object, y, x - 1);
		if (static_object[y][x + 1]->getChar() == 't') drop(movable_object, static_object, y, x + 1);
	}
}


void Board::fillBoard(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object) const
{	
	if (!(movable_object->getSpritePos().x > m_up_left.x && movable_object->getSpritePos().y > m_up_left.y && movable_object->getSpritePos().x > m_down_left.x  && movable_object->getSpritePos().y < m_down_left.y
		&& movable_object->getSpritePos().x < m_up_right.x && movable_object->getSpritePos().y > m_up_right.y && movable_object->getSpritePos().x < m_down_right.x && movable_object->getSpritePos().y < m_down_right.y)
		|| static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]->getChar() == 'b')
		for (int i = 0; i < static_object.size(); i++)
		{
			for (int j = 0; j < static_object[i].size(); j++)
			{
				if (static_object[i][j]->getChar() == 't')
				{
					Wall& wall = dynamic_cast<Wall&>(*static_object[i][j]);
					wall.Handle(m_texture_blue, 's');
				}
				else if (static_object[i][j]->getChar() == '1') 
					static_object[i][j]->setChar('t');
			}
		}
}


void Board::getGreenToBlue(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object) const
{
	if (!(movable_object->getSpritePos().x > m_up_left.x && movable_object->getSpritePos().y > m_up_left.y && movable_object->getSpritePos().x > m_down_left.x  && movable_object->getSpritePos().y < m_down_left.y
		&& movable_object->getSpritePos().x < m_up_right.x && movable_object->getSpritePos().y > m_up_right.y && movable_object->getSpritePos().x < m_down_right.x && movable_object->getSpritePos().y < m_down_right.y)
		|| static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]->getChar() == 'b')
	{
		for (auto& s : static_object)
		{
			for (int i = 0; i < s.size(); i++)
				if (s[i]->getChar() == 'g')
				{
					Wall& wall = dynamic_cast<Wall&>(*s[i]);
					wall.Handle(m_texture_blue, 'c');
				}
		}
	}
}


void Board::destroyTile(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object) const
{
	Wall& wall = dynamic_cast<Wall&>(*static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]);
	wall.Handle(m_texture_transparent, 'c');
}


void Board::buildTile(const std::unique_ptr<DynamicObject>& movable_object, staticO& static_object) const
{
	Wall& wall = dynamic_cast<Wall&>(*static_object[movable_object->getSpritePos().y / m_tile_size][movable_object->getSpritePos().x / m_tile_size]);
	wall.Handle(m_texture_light_blue, 'o');
}


void Board::restart(const std::string& str, dynamicO& movable_object, staticO& static_object) 
{
	movable_object.clear();
	static_object.clear();
	build(str, movable_object, static_object);
}
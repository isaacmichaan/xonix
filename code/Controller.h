#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "InfoBar.h"
class Board;
class DynamicObject;
class StaticObject;
typedef std::vector<std::unique_ptr<DynamicObject>> dynamicO;
typedef std::vector<std::vector<std::unique_ptr<StaticObject>>> staticO;

class Controller
{
private:
	sf::RenderWindow m_window;
	std::unique_ptr<Board> m_board;
	std::unique_ptr<InfoBar> m_info;
	std::ifstream m_file;
	std::string m_level;
	dynamicO m_movable_object;
	staticO m_static_object;
	const int m_tile_size = 18; // Size of tile; If Changed, need to do the same on Board and GameObject
public:
	Controller();
	~Controller();
	void run();
	void menu();
	void level();
	void speed();
	void window();
	bool gameOver();
	bool event();
	void move(std::unique_ptr<DynamicObject>&);
	void restart();
	void score();
	//void present();
	void draw();
};


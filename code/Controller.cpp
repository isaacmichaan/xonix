#include "Controller.h"
#include "Board.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include <iostream>

Controller::Controller()
{
	m_window.setFramerateLimit(60);
	m_board = std::make_unique<Board>();
	m_info = std::make_unique<InfoBar>();
	m_file.open("levels/level.txt");
	if (!m_file.good())
	{
		std::cout << "no such file" << std::endl;
		exit(0);
	}
}


Controller::~Controller()
{
	m_file.close();
}


void Controller::run()
{
	menu();
	level();
	srand(time(0));
	window();
}


void Controller::menu()
{
	sf::Texture menu;
	menu.loadFromFile("images/menu.png");
	sf::Sprite sprite(menu);
	m_window.create(sf::VideoMode(1280, 702), "Xonix Game!");
	while (m_window.isOpen())
	{
		bool start = event();
		if (start) break;
		m_window.draw(sprite);
		m_window.display();
	}
	m_window.create(sf::VideoMode(1512, 702), "Xonix Game!"); // If sf::VideoMode(1512, 702) changes, need to do the same on User::checkBorders
}


void Controller::level()
{
	m_file.exceptions(m_file.failbit | m_file.badbit);
	try {
		m_file >> m_level;
	}
	catch (std::exception e)
	{
		std::cout << e.what();
		exit(0);
	}
	restart();
}


void Controller::speed()
{
	for (auto& mo : m_movable_object) 
	{ 
		switch (mo->getChar())
		{
		case 'r':
			mo->setDelay(0.7);
		case 'l':
			mo->setDelay(0.1);
			break;
		case 'p':
			mo->setDelay(0.20);
			break;
		case 'y':
			mo->setDelay(0.1);
			break;
		case 'a':
			mo->setDelay(0.1);
			break;
		}
	}
}


void Controller::window()
{
	sf::Clock clock;
	
	sf::Music music;
	music.openFromFile("sounds/music.wav");
	music.setLoop(true);
	music.play();
	
	sf::SoundBuffer buffer;
	sf::Sound sound;

	while (m_window.isOpen())
	{
		if(gameOver())
			break;

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		event();

		for (auto& movable_object : m_movable_object) 
		{ 
			movable_object->setTimer(time);
			if (movable_object->getTimer() > movable_object->getDelay())
			{
				Controller::move(movable_object);
				if (movable_object->getLife())
				{
					buffer.loadFromFile("sounds/shotgun.wav");
					sound.setBuffer(buffer);
					sound.play();
					m_info->setLife(-1);
					restart();
					break;
				}
			}
		}
		score();
		//present();
		draw();
	}
}


bool Controller::gameOver()
{
	if (m_info->getLife() == 0)
	{
		sf::Texture gameover;
		gameover.loadFromFile("images/gameover.png");
		sf::Sprite sprite(gameover);
		int count = 0;
		while (count != 500)
		{
			m_window.clear(sf::Color(33, 97, 140));
			m_window.draw(sprite);
			m_window.display();
			count++;
		}
		return true;
	} return false;
}


bool Controller::event()
{
	sf::Event e;
	sf::Mouse b;

	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			exit(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.mouseButton.x > 390 && e.mouseButton.x < 890 && e.mouseButton.y > 290 && e.mouseButton.y < 350)
				return true;
			if (e.mouseButton.x > 420 && e.mouseButton.x < 850 && e.mouseButton.y > 530 && e.mouseButton.y < 580)
			{
				sf::Font font;
				font.loadFromFile("fonts/JOKERMAN.TTF");
				sf::Text text;
				
				text.setString(std::string(
					"This game is based on the popular Xonix, with much the same rules and objectives.\n" 
					"In the new version, you’re airborne, operating a flying machine.\n\n"
					
					"Master the field and be victorious"
					"AirXoniX is like the original Xonix,\n in that you are the controller of a device that moves around a field,\n"
					"which is populated by a number of monster sized balls.\n"
					"The aim of the game, \nas in the first version is that you must clear the balls away and create open field space.\n"
					"There are also mines to consider, which move around covered areas and there’s also a time limit.\n"
					"Collect the right bonuses to get life,\n raise your score and time and to slow down the advance of mines and balls.\n\n"

					"Classic game gets a modern twist\n"
					"This modern take on an old classic elevates the game to new heights,\n with a whole range of new monsters and exciting bonuses,\n" 
					"all presented in full 3D.The game is complemented with striking special effects and great 3D sound.\n"
					"\n\nPress right mouse key to return to menu ;)"
				));

				text.setCharacterSize(24);

				text.setStyle(sf::Text::Bold);

				text.setFont(font);

				while (1)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						break;
					m_window.clear(sf::Color(33, 97, 140));
					m_window.draw(text);
					m_window.display();
				}
			}
			if (e.mouseButton.x > 430 && e.mouseButton.x < 850 && e.mouseButton.y > 620 && e.mouseButton.y < 650)
				exit(0);
		}
	}
}


void Controller::move(std::unique_ptr<DynamicObject>& mo) //mo = movable_object
{
	if (mo->getChar() == 'r')
	{
		//שלא יסגור אם יש שומר בפנים
		for (auto& mo : m_movable_object)
		{
			if (mo->getChar() != 'r' && mo->getChar() != 'l' && mo->getChar() != 'a')
				m_board->drop(m_movable_object[0], m_static_object, mo->getSpritePos().y / m_tile_size, mo->getSpritePos().x / m_tile_size);
		}
		
		//שהכתום לא יסגור עם כחול בפנים
		for (auto& so : m_static_object)
		{
			for (int i = 0; i < so.size(); i++)
			{
				if (so[i]->getChar() == 'o')
					m_board->drop(m_movable_object[0], m_static_object, so[i]->getSpritePos().y / m_tile_size, so[i]->getSpritePos().x / m_tile_size);
			}
		}
		
		m_board->fillBoard(mo, m_static_object);//לשים כחול
		m_board->getGreenToBlue(mo, m_static_object);//לשנות את הירוק
		m_board->newTile(mo, m_static_object);//בניה של הירוק
	}
	
	//הכדור שהורס
	if (mo->getChar() == 'y' && mo->getDestroyTile())
		m_board->destroyTile(mo, m_static_object);
	
	//כובש ממוחשב שיבנה
	if (mo->getChar() == 'l' && mo->getBuildTile())
		m_board->buildTile(mo, m_static_object);
	mo->move(m_movable_object, m_static_object);
	mo->setTimer(0);
}


void Controller::restart()
{
	m_board->restart(m_level, m_movable_object, m_static_object);
	speed();
	m_info->setNewLevel();
}


void Controller::score()
{
	static bool y = true;
	static int count = 0;
	if (y)
	{
		for (const auto& so : m_static_object)
			for (int i = 0; i < so.size(); i++)
				if (so[i]->getChar() != '0' && so[i]->getChar() != '2')
					count++;
		y = false;
	}
	m_info->setScore(m_static_object, count);
	if (m_info->getScore() >= 0.50 * count)
	{
		y = true;
		level();
	}
}

//void Controller::present()
//{
//	static int count;
//	static int i, j;
//	count++;
//
//	if (count == 50)
//	{
//		int x = m_static_object.size();
//		int y = m_static_object[0].size();
//
//		i = rand() % x;
//		j = rand() % j;
//
//		m_static_object[i][j]
//
//	}
//
//	if (count == 200)
//	{
//		m_static_object[i][j]
//		count == 0;
//	}
//}

void Controller::draw()
{
	m_window.clear(sf::Color(33, 97, 140));
	
	m_info->draw(m_window);

	for (const auto& so : m_static_object) 
		for (int i = 0; i < so.size(); i++)
			so[i]->draw(m_window);
	
	for (const auto& mo : m_movable_object) 
		mo->draw(m_window);

	m_window.display();
}
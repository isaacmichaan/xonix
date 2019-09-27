//---------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef WStateH
#define WStateH
class Wall;
//---------------------------------------------------------------------------
class WState
{
   public:
	 virtual void Continuous(Wall&, const sf::Texture&) = 0;
	 virtual void Skipped(Wall&, const sf::Texture&) { std::cout << "WStateRONG"; };
	 virtual void Tile(Wall&, const sf::Texture&) { std::cout << "WStateRONG"; };
};
#endif

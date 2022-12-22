#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::RectangleShape
{
public:
	Tile();
	~Tile();

public:
	bool p_falling;
	sf::Time p_fallTime;
};



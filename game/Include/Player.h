#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>



namespace phys 
{
	class Player
	{
	public:
		Player();
		~Player();
		float p_moveX;
		float p_moveY;
		sf::Vector2f p_lastPosition;
		sf::Vector2f p_position;
		sf::Vector2f p_velocity;
		float p_width;
		float p_height;
		void proccessEvent(sf::Keyboard::Key key, bool Checkpressed);
		void Update();
	private :
		sf::RectangleShape player;
		bool up;
		bool down;
		bool left;
		bool right;
	};
};

#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

namespace phys 
{
	class Platform
	{
	public:
		Platform();
		~Platform();
		unsigned int p_id;
		sf::Vector2f p_position;
		float p_width;
		float p_height;
		int p_type;
		bool p_collisionTop;
		bool p_collisionBottom;
		bool p_collisionLeft;
		bool p_collisionRight;
		bool p_falling;
		float p_surfaceVelocity;

	};
};
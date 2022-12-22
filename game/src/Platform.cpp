#include "Platform.h"



phys::Platform::Platform()
{
	p_collisionBottom = false;
	p_collisionLeft = false;
	p_collisionRight = false;
	p_collisionTop = false;
	p_falling = false;
	p_height = 32;
	p_width = 32;
	p_type = 1;
	p_surfaceVelocity = 0;
	p_position = sf::Vector2f(0, 0);
}


phys::Platform::~Platform()
{
}

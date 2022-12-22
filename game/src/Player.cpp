#include "Player.h"



phys::Player::Player()
{
	up = false;
	down = false;
	left = false;
	right = false;
	p_moveX = 0;
	p_moveY = 0;
	p_lastPosition = sf::Vector2f(0, 0);
	p_position = sf::Vector2f(0, 0);
	p_velocity = sf::Vector2f(0, 0);
	p_width = 32.f;
	p_height = 32.f;
}


phys::Player::~Player()
{
}

void phys::Player::proccessEvent(sf::Keyboard::Key key, bool Checkpressed)
{
	if (Checkpressed == true) {
		if (key == sf::Keyboard::W) {
			up = true;
		}
		if (key == sf::Keyboard::A) {
			left = true;
		}
		if (key == sf::Keyboard::S) {
			down = true;
		}
		if (key == sf::Keyboard::D) {
			right = true;
		}
	}
	if (Checkpressed == false) {
		up = false;
		down = false;
		left = false;
		right = false;
	}
}

void phys::Player::Update()
{
	sf::Vector2f movement;
	if (up) {
		movement.y += 1.f;
	}
	if (down) {
		movement.y -= 1.f;
	}
	if (left) {
		movement.x -= 1.f;
	}
	if (right) {
		movement.x += 1.f;
	}

	player.move(movement);
}

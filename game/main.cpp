#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Platform.h>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Player.h>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Collision.h>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Easing.h>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Tile.h>



int main(void)
{
	const sf::Vector2f tilesize = sf::Vector2f(32, 32);
	const int NumofPlatform = 24;

	float GRAVITY = 0.f;
	sf::RenderWindow window(sf::VideoMode(800, 600), "JUMP!!!", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Event event;

	sf::View mainView(sf::FloatRect(0.f, 0.f, 1200.f, 800.f));
	window.setView(mainView);

	phys::Collision Collisions;

	phys::Platform platform[NumofPlatform];
	for (int i = 0; i < NumofPlatform; i++) {
		platform[i].p_id = i;
		platform[i].p_height = tilesize.y;
		platform[i].p_width = tilesize.x * 4;
		platform[i].p_type = phys::PlatType::platform;
	}

	//placing the platform

	//regular type platform
	platform[0].p_position = sf::Vector2f(0.f, window.getSize().y - 32.f);
	platform[1].p_position = sf::Vector2f(0.f, 356.f);
	platform[2].p_position = sf::Vector2f(480.f, window.getSize().y - 192.f);
	platform[3].p_position = sf::Vector2f(0.f, 96.f);
	platform[4].p_position = sf::Vector2f(640.f, 224.f);
	platform[5].p_position = sf::Vector2f(480.f, window.getSize().y - 32.f);
	platform[6].p_position = sf::Vector2f(672.f, window.getSize().y - 260.f);
	platform[7].p_position = sf::Vector2f(96.f, window.getSize().y - 128.f);
	platform[8].p_position = sf::Vector2f(640, window.getSize().y - 160.f);
	platform[9].p_position = sf::Vector2f(640.f, 64.f);
	platform[10].p_position = sf::Vector2f(292, window.getSize().y - 128.f);

	//conveyor type platform
	platform[11].p_position = sf::Vector2f(window.getSize().x / 4.f, window.getSize().y / 2.f);
	platform[11].p_width = tilesize.x * 10;
	platform[11].p_height = tilesize.y;
	platform[11].p_type = phys::PlatType::conveyor;
	platform[11].p_surfaceVelocity = 12.f;

	//moving type platform
	platform[12].p_height = tilesize.y / 8;
	platform[12].p_width = tilesize.x * 5;
	platform[12].p_position = sf::Vector2f(window.getSize().x / 4, window.getSize().y / 4);
	platform[12].p_type = phys::PlatType::moving;
	int platformDir = 1;
	float platformVelocity = 0.f;

	//jumpthrough type platform
	platform[13].p_width = tilesize.x;
	platform[13].p_height = tilesize.y / 8.f;
	platform[13].p_position = sf::Vector2f(160.f, window.getSize().y - 224.f);
	platform[13].p_type = phys::PlatType::jumpthrough;

	platform[14].p_width = tilesize.x;
	platform[14].p_height = tilesize.y / 8.f;
	platform[14].p_position = sf::Vector2f(576.f, window.getSize().y - 288.f);
	platform[14].p_type = phys::PlatType::jumpthrough;

	//falling type platform
	platform[15].p_width = tilesize.x;
	platform[15].p_height = tilesize.y;
	platform[15].p_position = sf::Vector2f(192.f, 64.f);
	platform[15].p_type = phys::PlatType::falling;

	platform[16].p_width = tilesize.x;
	platform[16].p_height = tilesize.y;
	platform[16].p_position = sf::Vector2f(256.f, 64.f);
	platform[16].p_type = phys::PlatType::falling;

	platform[17].p_width = tilesize.x;
	platform[17].p_height = tilesize.y;
	platform[17].p_position = sf::Vector2f(384.f, 64.f);
	platform[17].p_type = phys::PlatType::falling;

	platform[18].p_width = tilesize.x;
	platform[18].p_height = tilesize.y;
	platform[18].p_position = sf::Vector2f(320, 64.f);
	platform[18].p_type = phys::PlatType::falling;

	platform[19].p_width = tilesize.x;
	platform[19].p_height = tilesize.y;
	platform[19].p_position = sf::Vector2f(448.f, 64.f);
	platform[19].p_type = phys::PlatType::falling;

	//vanishing type platform
	platform[20].p_width = tilesize.x;
	platform[20].p_height = tilesize.y;
	platform[20].p_position = sf::Vector2f(192.f, -32.f);
	platform[20].p_type = phys::PlatType::vanishing;

	platform[21].p_width = tilesize.x;
	platform[21].p_height = tilesize.y;
	platform[21].p_position = sf::Vector2f(256.f, -32.f);
	platform[21].p_type = phys::PlatType::vanishing;

	platform[23].p_width = tilesize.x;
	platform[23].p_height = tilesize.y;
	platform[23].p_position = sf::Vector2f(320.f, -32.f);
	platform[23].p_type = phys::PlatType::vanishing;

	//coloring
	Tile tiles[NumofPlatform];
	for (int i = 0; i < NumofPlatform; i++) {
		tiles[i].setPosition(platform[i].p_position);
		tiles[i].setSize(sf::Vector2f(platform[i].p_width, platform[i].p_height));
		switch (platform[i].p_type)
		{
		case phys::PlatType::platform:
			tiles[i].setFillColor(sf::Color::Blue);
			break;
		case phys::PlatType::conveyor:
			tiles[i].setFillColor(sf::Color::Red);
			break;
		case phys::PlatType::falling:
			tiles[i].setFillColor(sf::Color::Green);
			break;
		case phys::PlatType::jumpthrough:
			tiles[i].setFillColor(sf::Color::Cyan);
			break;
		case phys::PlatType::moving:
			tiles[i].setFillColor(sf::Color::Yellow);
			break;
		case phys::PlatType::vanishing:
			tiles[i].setFillColor(sf::Color::Magenta);
		default:
			break;
		}
	}

	//player set up
	phys::Player YOLO;
	YOLO.p_position = sf::Vector2f(200 , -50);
	YOLO.p_width = tilesize.x;
	YOLO.p_height = tilesize.y;
	YOLO.p_velocity = sf::Vector2f(0, 0);
	YOLO.p_lastPosition = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
	YOLO.p_moveX = 0.f;
	YOLO.p_moveY = 0.f;

	sf::RectangleShape player;
	player.setFillColor(sf::Color::White);
	player.setSize(sf::Vector2f(tilesize.x, tilesize.y));
	player.setPosition(YOLO.p_position);

	//setting time variables
	sf::Clock tickclock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time duration = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Time jumpTime = sf::Time::Zero;
	sf::Time VanishingTime = sf::Time::Zero;
	sf::Time springTime = sf::Time::Zero;
	int oddEven = 1;
	float alpha = 0.f;
	bool springPeak = false;
	bool canSpring = false;
	bool springsprung = false;

	int turbo = 1;

	sf::Vector2f speed = sf::Vector2f(0.f, 0.f);

	bool intersection = false;
	unsigned int type = phys::PlatType::none;
	bool collisionTop = false;
	bool collisionBottom = false;
	bool collisionLeft = false;
	bool collisionRight = false;
	bool canjump = false;
	bool jumped = false;
	unsigned int jumpcount = 0;
	double starting = 0.0001;


	bool running = true;
	while (running) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
			
			/*if (event.type == sf::Event:: KeyPressed) {
				YOLO.proccessEvent(event.key.code, true);
			}
			if (event.type == sf::Event::KeyReleased) {
				YOLO.proccessEvent(event.key.code, false);
			}*/
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Escape:
				{
					window.close();
					return 0;
				}
				break;
				case sf::Keyboard::A: {
					speed.x -= 10.f;
					player.move(speed);
				}
				case sf::Keyboard::D: {
					speed.x += 10.f;
					player.move(speed);
				}
				default:
					break;
				}
			}
		}
		sf::Time elapsedtime = tickclock.restart();
		timeSinceLastUpdate += elapsedtime;
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			//moving platform accumulator
			if (duration.asSeconds() >= 4.f) {
				platformDir *= -1;
				duration = sf::Time::Zero;
			}
			else {
				duration += timePerFrame;
			}

			//moving platform updates
			if (duration.asSeconds() <= 3.f) {
				platformVelocity = timePerFrame.asSeconds()*(platformDir * 700.f * math::Easing::quadraticEaseInOut(duration.asSeconds(), 0.f, 1.f, 3.f));
			}
			else {
				platformVelocity = 0.f;
			}

			//update posision of moving platform before player updates
			platform[12].p_position.x += platformVelocity;
			tiles[12].setPosition(platform[12].p_position);

			for (int i = 0; i < NumofPlatform; ++i) {
				bool collided = platform[i].p_falling;

				if (collided && tiles[i].p_fallTime.asSeconds() > .5f) {
					tiles[i].p_fallTime = sf::Time::Zero;
				}
				else {
					tiles[i].p_fallTime += timePerFrame;
				}

				if (collided && tiles[i].p_fallTime.asSeconds() > .5f) {
					tiles[i].p_falling = true;
				}
			}
			//update for falling platform
			for (int i = 0; i < NumofPlatform; i++) {
				if (tiles[i].p_falling && platform[i].p_falling) {
					platform[i].p_position = sf::Vector2f(-9999, 0);
					tiles[i].move(0.f, timePerFrame.asSeconds()*1000.f);
				}
			}

			//compute time and reset for vanishing platform
			if (VanishingTime.asSeconds() > 2.f) {
				VanishingTime = sf::Time::Zero;
				oddEven *= -1;
			}
			else {
				VanishingTime += timePerFrame;
			}

			//making the platform vanish and reappear
			if (oddEven == 1) {
				for (int i = 20; i < 24; i++) {
					if (i % 2 == 0) {
						if (VanishingTime.asSeconds() < 1.f) {
							alpha = math::Easing::sineEaseIn(VanishingTime.asSeconds(), 0.f, 255.f, 1.f);
							tiles[i].setFillColor(sf::Color(255, 0, 255, 255 - (unsigned int)alpha));
						}
						else {
							tiles[i].setFillColor(sf::Color(255, 0, 255, 0));
						}
						if (tiles[i].getFillColor().a <= 0) {
							platform[i].p_position = sf::Vector2f(-9999, 0);
						}
					}
					else {
						if (VanishingTime.asSeconds() < 1.f) {
							alpha = math::Easing::sineEaseIn(VanishingTime.asSeconds(), 0.f, 255.f, 1.f);
							tiles[i].setFillColor(sf::Color(255, 0, 255, (unsigned int)alpha));
						}
						else {
							tiles[i].setFillColor(sf::Color(255, 0, 255, 255));
						}
						platform[i].p_position = tiles[i].getPosition();
					}
				}
			}
			else {
				for (int i = 20; i < 24; i++) {
					if (i % 2 == 0) {
						if (VanishingTime.asSeconds() < 1.f) {
							alpha = math::Easing::sineEaseIn(VanishingTime.asSeconds(), 0.f, 255.f, 1.f);
							tiles[i].setFillColor(sf::Color(255, 0, 255, 255 - (unsigned int)alpha));
						}
						else {
							tiles[i].setFillColor(sf::Color(255, 0, 255, 0));
						}
						platform[i].p_position = tiles[i].getPosition();

					}
					else {
						if (VanishingTime.asSeconds() < 1.f) {
							alpha = math::Easing::sineEaseIn(VanishingTime.asSeconds(), 0.f, 255.f, 1.f);
							tiles[i].setFillColor(sf::Color(255, 0, 255, (unsigned int)alpha));
						}
						else {
							tiles[i].setFillColor(sf::Color(255, 0, 255, 255));
						}
						if (tiles[i].getFillColor().a <= 0) {
							platform[i].p_position = sf::Vector2f(-9999, 0);
						}
					}
				}
			}

			//about jump and jumpcount
			if (jumpcount > 1) {
				jumpTime = sf::Time::Zero;
			}
			else {
				jumpTime += timePerFrame;
			}
			//if jump pressed and the timer less than 0.5 seconds, player can jump
			canjump = jumped && jumpTime.asSeconds() < 0.4f ? true : false;

			//updates
			//intersection = YOLO.p_position.y + YOLO.p_height >= Collisions.getPlatInfo().P_position.y - 2.f || YOLO.p_position.y + YOLO.p_height <= Collisions.getPlatInfo().P_position.y + Collisions.getPlatInfo().p_height || YOLO.p_position.x + YOLO.p_width >= Collisions.getPlatInfo().P_position.x || YOLO.p_position.x + YOLO.p_width <= Collisions.getPlatInfo().P_position.x + Collisions.getPlatInfo().p_width + YOLO.p_width;
			if (YOLO.p_position.y + YOLO.p_height >= Collisions.getPlatInfo().P_position.y - 2.f && YOLO.p_position.y + YOLO.p_height <= Collisions.getPlatInfo().P_position.y + Collisions.getPlatInfo().p_height && YOLO.p_position.x + YOLO.p_width >= Collisions.getPlatInfo().P_position.x && YOLO.p_position.x + YOLO.p_width <= Collisions.getPlatInfo().P_position.x + Collisions.getPlatInfo().p_width + YOLO.p_width) {
				intersection = true;
			}
			else {
				intersection = false;
			}

			//get platform info
			type = Collisions.getPlatInfo().p_type;

			//getting collision information
			collisionLeft = Collisions.GetCollisionInfo().p_collisionLeft;
			collisionBottom = Collisions.GetCollisionInfo().p_collisionBottom;
			collisionRight = Collisions.GetCollisionInfo().p_collisionRight;
			collisionTop = Collisions.GetCollisionInfo().p_collisionTop;

			//update position of square and checking dead zones
			if ((speed.x > 15.f && !collisionLeft) || (speed.x < -15.f && !collisionRight)) {
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			else {
				speed.x = 0.f;
			}
			if (canjump) {
				if (jumpTime.asSeconds() < .2f && !collisionTop) {
					YOLO.p_position.y += -800.f*timePerFrame.asSeconds() + GRAVITY;
				}
				else if (jumpTime.asSeconds() > .2f && !collisionTop) {
					YOLO.p_position.y += GRAVITY - 13.9;
				}
			}

			//reduce stickiness
			if (collisionBottom) {
				YOLO.p_position.y = YOLO.p_lastPosition.y;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//check contact with static platform
			if (type == phys::PlatType::platform && collisionBottom) {
				GRAVITY = 0.f;
				YOLO.p_position.x = turbo*speed.x*timePerFrame.asSeconds();
			}
			// sticky ceiling solved
			else if (collisionTop && (!collisionLeft || !collisionRight)) {
				YOLO.p_position.y = YOLO.p_lastPosition.y + 0.5f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//sticky wall problem solved
			else if (!collisionBottom && (collisionLeft || collisionRight)) {
				YOLO.p_position.y += GRAVITY;
				YOLO.p_position.x = YOLO.p_lastPosition.x;
			}
			//check contact with jumpthrough platform
			else if (type == phys::PlatType::jumpthrough && collisionBottom) {
				GRAVITY = 0.f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//check contact with conveyor platform
			else if (type == phys::PlatType::conveyor && collisionBottom) {
				GRAVITY = 0.f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//check contact with moving platform
			else if (type == phys::PlatType::moving && collisionBottom) {
				GRAVITY = 0.f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//check contact with falling platform
			else if (collisionBottom && intersection && type == phys::PlatType::falling) {
				platform[Collisions.getPlatInfo().p_id].p_falling = true;
				GRAVITY = 0.f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}
			//check contact with vanishing platform
			else if (type == phys::PlatType::vanishing && collisionBottom) {
				GRAVITY = 0.f;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();

			}

			else {
				if (GRAVITY < 20.f) {
					GRAVITY += .4f;
				}
				else {
					GRAVITY = 20.f;
				}
				YOLO.p_position.y += GRAVITY;
				YOLO.p_position.x += turbo*speed.x*timePerFrame.asSeconds();
			}

			Collisions.setcollisionInfo(false, false, false, false);

			for (int i = 0; i < 3; i++) {
				Collisions.ResolveCollision(&YOLO, platform, NumofPlatform);
			}
			YOLO.p_lastPosition = YOLO.p_position;

			player.setPosition(YOLO.p_position);
		}
		mainView.setCenter(player.getPosition());

		window.clear();
		window.setView(mainView);

		for (auto i : tiles) {
			window.draw(i);
		}

		window.draw(player);

		window.display();
	}
	return 0;
}
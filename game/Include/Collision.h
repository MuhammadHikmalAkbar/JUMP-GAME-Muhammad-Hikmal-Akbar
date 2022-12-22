#pragma once

#include <stdlib.h>
#include <algorithm>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Platform.h>
#include <C:\Users\M Hikmal Akbar\Documents\Visual Studio 2015\Projects\Game Project\Game Project\Player.h>

namespace phys
{
	struct collision
	{
		float time = 0.f;
		float surfaceArea = 0.f;
		int axis = 0;
	};

	struct collisionInfo
	{
		bool p_collisionTop = false;
		bool p_collisionBottom = false;
		bool p_collisionLeft = false;
		bool p_collisionRight = false;
	};

	enum PlatType //tipe platform dari game
	{
		none = 0,
		platform = 1, //tipe biasa
		conveyor = 2, //seperti conveyor
		moving = 3, //platform bergerak
		jumpthrough = 4, //tipe tembus
		falling = 5, //platform jatuh
		vanishing = 6, //yang bisa menghilang
	};

	struct PlatInfo
	{
		unsigned int p_type = phys::PlatType::none;
		unsigned int p_id = 0;
		float p_width = 0.f;
		float p_height = 0.f;
		bool p_collisionTop = false;
		bool p_collisionBottom = false;
		bool p_collisionLeft = false;
		bool p_collisionRight = false;
		bool p_falling = false;
		sf::Vector2f P_position = sf::Vector2f(0, 0);
		float p_surfaceVelocity = 0.f;
	};

	class Collision
	{
	public:
		Collision();
		virtual ~Collision();

		static PlatInfo p_platInfo;
		static collisionInfo p_collisionInfo;
		static bool p_collisionTop;
		static bool p_collisionBottom;
		static bool p_collisionLeft;
		static bool p_collisionRight;

		void ResolveCollision(class Player *player, class Platform *platform, int numOfPlatform);
		void setPlatInfo(Platform &platform);
		PlatInfo getPlatInfo() { return p_platInfo; };

		inline void setcollisionInfo(bool t, bool b, bool l, bool r);
		collisionInfo GetCollisionInfo() { return p_collisionInfo; };



	private:
		static bool movingToStaticIntersectionTest(class Player * player, class Platform platform, struct collision * outCollision);
		static void resolveStaticCollision(class Player * player, struct collision collision, float timesliceRemaining);

	};
}
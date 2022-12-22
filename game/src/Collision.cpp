#include "Collision.h"

const int X_Axis = 1;
const int Y_Axis = 2;

const float COLLISION_EPSILON = 0.00001f; //to rounding float item
const float TIMESLICE_EPSILON = 0.00001F; //to rounding float item
const int MAX_TIMESLICE_SUBDIVISION = 32; //prevent infinite loop while collitioning

void phys::Collision::setcollisionInfo(bool t, bool b, bool l, bool r) {
	p_collisionInfo.p_collisionTop = t;
	p_collisionInfo.p_collisionBottom = b;
	p_collisionInfo.p_collisionLeft = l;
	p_collisionInfo.p_collisionRight = r;
}

void phys::Collision::setPlatInfo(Platform &platform) {
	p_platInfo.p_type = platform.p_type;
	p_platInfo.p_id = platform.p_id;
	p_platInfo.p_height = platform.p_height;
	p_platInfo.p_width = platform.p_width;
	p_platInfo.p_collisionBottom = platform.p_collisionBottom;
	p_platInfo.p_collisionLeft = platform.p_collisionLeft;
	p_platInfo.p_collisionRight = platform.p_collisionRight;
	p_platInfo.p_collisionTop = platform.p_collisionTop;
	p_platInfo.p_falling = platform.p_falling;
	p_platInfo.P_position = platform.p_position;
	p_platInfo.p_surfaceVelocity = platform.p_surfaceVelocity;
}

bool phys::Collision::movingToStaticIntersectionTest(class Player * player, class Platform platform, struct collision * outCollision) {
	float timeX = 0.f, timeY = 0.f;
	bool p_collisionX = false;
	bool p_collisionY = false;
	float newX = 0.f, newY = 0.f;
	float staticLeft, staticRight, staticBottom, staticTop;
	float MovingLeft, MovingRight, MovingBottom, MovingTop;
	float lastMoveLeft, lastMoveRight, lastMoveBottom, lastMoveTop;

	staticLeft = platform.p_position.x;
	staticRight = staticLeft + platform.p_width;
	staticBottom = platform.p_position.y;
	staticTop = staticBottom + platform.p_height;
	MovingLeft = player->p_position.x;
	MovingRight = MovingLeft + player->p_width;
	MovingBottom = player->p_position.y;
	MovingTop = MovingBottom + player->p_height;
	lastMoveLeft = player->p_lastPosition.x;
	lastMoveRight = lastMoveLeft + player->p_width;
	lastMoveBottom = player->p_lastPosition.y;
	lastMoveTop = lastMoveBottom + player->p_height;

	if (std::min(MovingBottom, lastMoveBottom) < staticTop - COLLISION_EPSILON && std::max (MovingTop, lastMoveTop) > staticBottom + COLLISION_EPSILON)
	{
		if (lastMoveRight <= staticLeft + COLLISION_EPSILON && MovingRight > staticLeft + COLLISION_EPSILON)
		{
			p_collisionX = true;
			p_collisionRight = true;
			p_collisionLeft = false;
			platform.p_collisionRight = true;
			platform.p_collisionLeft = false;
			timeX = (staticLeft - lastMoveRight) / (MovingLeft - lastMoveLeft);
		}
		
		else if (lastMoveLeft >= staticRight - COLLISION_EPSILON && MovingLeft < staticRight - COLLISION_EPSILON)
		{
			p_collisionX = true;
			p_collisionRight = false;
			p_collisionLeft = true;
			platform.p_collisionRight = false;
			platform.p_collisionLeft = true;
			timeX = (staticRight - lastMoveLeft) / (MovingLeft - lastMoveLeft);
		}

		if (p_collisionX) 
		{
			newY = lastMoveBottom + (MovingBottom - lastMoveBottom) * timeX;
			if (newY >= staticTop - COLLISION_EPSILON || newY + platform.p_height <= staticBottom + COLLISION_EPSILON) {
				p_collisionX = false;
				p_collisionRight = false;
				p_collisionLeft = false;
				platform.p_collisionRight = false;
				platform.p_collisionLeft = false;
			}
		}
		else
		{
			p_collisionRight = false;
			p_collisionLeft = false;
			platform.p_collisionRight = false;
			platform.p_collisionLeft = false;
		}
	}
	

	if (std::min(MovingLeft, lastMoveLeft) < staticRight - COLLISION_EPSILON && std::max(MovingRight, lastMoveRight) > staticLeft + COLLISION_EPSILON) {
		if (lastMoveTop <= staticBottom + COLLISION_EPSILON && MovingTop > staticBottom + COLLISION_EPSILON) {
			p_collisionY = true;
			p_collisionBottom = true;
			p_collisionTop = false;
			platform.p_collisionBottom = true;
			platform.p_collisionTop = false;
			timeY = (staticBottom - lastMoveTop) / (MovingBottom - lastMoveBottom);
		}
		else if (lastMoveBottom >= staticTop - COLLISION_EPSILON && MovingBottom < staticTop - COLLISION_EPSILON) {
			p_collisionTop = true;
			p_collisionBottom = false;
			platform.p_collisionTop = true;
			platform.p_collisionBottom = false;

			if (platform.p_type == phys::PlatType::jumpthrough) {
				p_collisionY = false;
			}
			else
			{
				p_collisionY = true;
			}
			timeY = (staticTop - lastMoveBottom) / (MovingBottom - lastMoveBottom);
		}
		if (p_collisionX) {
			newX = lastMoveLeft + (MovingLeft - lastMoveLeft) * timeY;
			if (newX >= staticRight - COLLISION_EPSILON || newY + platform.p_width <= staticLeft + COLLISION_EPSILON) {
				p_collisionY = false;
				p_collisionTop = false;
				p_collisionBottom = false;
				platform.p_collisionTop = false;
				platform.p_collisionBottom = false;
			}
		}
		else {
			p_collisionTop = false;
			p_collisionBottom = false;
			platform.p_collisionTop = false;
			platform.p_collisionBottom = false;
		}
	}
	
	if (p_collisionX || p_collisionY) {
		
		if (!p_collisionX || (p_collisionY && timeY < timeX)) {
			outCollision->time = timeY;
			outCollision->axis = Y_Axis;
			outCollision->surfaceArea = std::min(staticRight, newX + player->p_width) - std::max(staticLeft, newX);
			return true;
		}

		outCollision->time = timeX;
		outCollision->axis = X_Axis;
		outCollision->surfaceArea = std::min(staticTop, newY + player->p_height) - std::max(staticBottom, newY);
		return true;
	}

	return false;

}

void phys::Collision::resolveStaticCollision(class Player * player, struct collision collision, float timesliceRemaining) {
	player->p_position.x = player->p_lastPosition.x + (player->p_position.x - player->p_lastPosition.x) * collision.time;
	player->p_position.y = player->p_lastPosition.y + (player->p_position.y - player->p_lastPosition.y) * collision.time;

	if (collision.axis == X_Axis) {
		player->p_velocity.x = 0.0f;
	}
	else {
		player->p_velocity.y = 0.0f;
	}

	player->p_lastPosition = player->p_position;
	player->p_position.x += player->p_velocity.x * (1.0f - collision.time) * timesliceRemaining;
	player->p_position.y += player->p_velocity.y * (1.0f - collision.time) * timesliceRemaining;
}


void phys::Collision::ResolveCollision(class Player *player, class Platform *platform, int numOfPlatform) {
	
	struct collision collision, bestCollision;
	bool collided;
	int platformIndex;
	float timesliceRemaining;
	int numOfTimesSubdivided;

	timesliceRemaining = 1.0f;
	numOfTimesSubdivided = 0;

	while (timesliceRemaining > TIMESLICE_EPSILON) {
		bestCollision.time = 1.0f + TIMESLICE_EPSILON;
		collided = false;

		for (platformIndex = 0; platformIndex < numOfPlatform; platformIndex++) {
			if (movingToStaticIntersectionTest(player, platform[platformIndex], &collision)) {
				setPlatInfo(platform[platformIndex]);
				if (collision.time < bestCollision.time ||
					(collision.time < bestCollision.time + TIMESLICE_EPSILON &&
						collision.surfaceArea > bestCollision.surfaceArea)) {
					collided = true;
					bestCollision = collision;
					setcollisionInfo(p_collisionTop, p_collisionBottom, p_collisionLeft, p_collisionRight);
				}
			}
		}

		if (!collided) {
			break;
		}

		resolveStaticCollision(player, bestCollision, timesliceRemaining);

		timesliceRemaining = (1.0f - bestCollision.time) * timesliceRemaining;
		numOfTimesSubdivided++;

		if (numOfTimesSubdivided > MAX_TIMESLICE_SUBDIVISION) {
			printf ("Warning Max timesilce reached, collision may be unresolved\n");
			break;
		}
	}
}

phys::PlatInfo phys::Collision::p_platInfo;
phys::collisionInfo phys::Collision::p_collisionInfo;
bool phys::Collision::p_collisionTop = false;
bool phys::Collision::p_collisionBottom = false;
bool phys::Collision::p_collisionLeft = false;
bool phys::Collision::p_collisionRight = false;


phys::Collision::Collision()
{
}

phys::Collision::~Collision()
{
}

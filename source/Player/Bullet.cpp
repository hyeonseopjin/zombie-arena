#include "Bullet.h"
#include "../Utils/TextureHorder.h"
#include "../Utils/Utils.h"
#include "../Zombie/Zombie.h"
#include <iostream>

Bullet::Bullet() : speed(DEFAULT_SPEED), isActive(false)
{
	shape.setSize(Vector2f(30, 10));
	Utils::SetOrigin(shape, Pivots::CC);
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}

bool Bullet::IsActive()
{
	return isActive;
}


void Bullet::Shoot(Vector2f pos, Vector2f dir)
{

	SetActive(true);

	distance = 0.f;
	position = pos;
	shape.setPosition(position);
	direction = Utils::Normalize(dir);	// normalized
	float degree = Utils::GetAngle(position, position + direction);
	shape.setRotation(degree);
}

void Bullet::Stop()
{
	SetActive(false);
}

void Bullet::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	FloatRect bounds = shape.getGlobalBounds();
	
	for(auto zombie : zombies)
	{
		if (zombie->IsAlive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();
				return true;
			}
		}
	}
	return false;
}

RectangleShape Bullet::GetShape()
{
	return shape;
}

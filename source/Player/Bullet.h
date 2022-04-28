#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/inputMgr.h"
#include <cmath>

using namespace sf;
using namespace std;

class Zombie;

class Bullet
{
private:
	const float DEFAULT_SPEED = 2000.f;
	const float DEFAULT_DISTANCE = 1500.f;

	bool isActive;

	RectangleShape shape;

	Vector2f position;
	Vector2f direction;
	float speed;
	float distance;

public:
	Bullet();
	//Bullet(int bc);
	void SetActive(bool active);
	bool IsActive();

	void Shoot(Vector2f pos, Vector2f dir);
	void Stop();

	void Update(float dt);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	RectangleShape GetShape();
};


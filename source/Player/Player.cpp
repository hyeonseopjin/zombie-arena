#include "Player.h"
#include "../Utils/Utils.h"
#include "../Utils/TextureHorder.h"
#include <iostream>

Player::Player() : speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), arena(),
resolustion(), tileSize(0.f), immuneMs(START_IMMUNE_MS),
textureFileName("graphics/player.png"),
distanceToMuzzle(45.f), curClip(BULLETS_IN_GUN), highClip(BULLET_NUM), timer(DELAY_TIME), reloading(false), playerDamamge(PLAYER_DAMAGE)
{
	sprite.setTexture(TextureHorder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, Pivots::CC);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unuseBullets.push_back(new Bullet());
	}
}

Player::~Player()
{
	for (auto bullet : unuseBullets)
	{
		delete bullet;
	}
	unuseBullets.clear();
	for (auto bullet : useBullets)
	{
		delete bullet;
	}
	useBullets.clear();
}

void Player::Shoot(Vector2f dir)
{
	dir = Utils::Normalize(dir);
	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unuseBullets.empty())
	{
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
		{
			unuseBullets.push_back(new Bullet());
		};
	}

	Bullet* bullet = unuseBullets.front();
	unuseBullets.pop_front();
	useBullets.push_back(bullet);
	bullet->Shoot(spawnPos, dir);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = this->arena.width * 0.5f;
	position.y = this->arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	// 0.2초 동안은 안맞게
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
	{
		std::cout << timeHit.asSeconds() << std::endl;
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGlobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

int Player::GetClip()
{
	return curClip;
}

int Player::GetClipSum()
{
	return highClip;
}

void Player::SetBul(int bul)
{
	curClip += bul;
}

void Player::SetHiBul(int bul)
{
	highClip += bul;
}

void Player::Update(float dt, IntRect arena)
{
	if (reloading)
	{
		rebar.Reload(dt);
		if (rebar.GetBar() < 0.2f)
		{
			curClip = 5;
			rebar.SetBer();
			reloading = false;
		}
	}

	// 사용자 입력에 맞춰 
	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length > 1) // 키입력이 있을 때 // 벡터의 노멀라이즈
	{
		dir /= length;
	}

	// 이동 
	// // 좀비가 이동할 방향, 스피드, dt를 사용하면 좀비 이동도 동일(dir만 수정해주자)
	position += dir * speed * dt;
	
	const int TILE_SIZE = 50;
	/// 플레이어 벽 충돌
	if (position.x < arena.left + TILE_SIZE)
	{
		position.x = arena.left + TILE_SIZE;
	}
	else if (position.x > arena.width - TILE_SIZE)
	{
		position.x = arena.width - TILE_SIZE;
	}
	else if (position.y < arena.top + TILE_SIZE)
	{
		position.y = arena.top + TILE_SIZE;
	}
	else if (position.y > arena.height - TILE_SIZE)
	{
		position.y = arena.height - TILE_SIZE;
	}

	sprite.setPosition(position);

	// 회전. 삼각함수 atan 사이값 구하기
	Vector2i mousePos = InputMgr::GetMousePosition();
	Vector2i mouseDir;

	// 중점으로부터 마우스포지션(화면 상의 위치로 정해줘야 하기 떄문에 -resolustion.x)
	mouseDir.x = mousePos.x - resolustion.x * 0.5f;
	mouseDir.y = mousePos.y - resolustion.y * 0.5f;
	
	/*mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;*/

	// 회전(마우스 방향 기준으로)
	float radian = atan2(mouseDir.y, mouseDir.x); // 라디안단위라 디그리로 변경해야함
	float degree = radian * 180 / 3.141592f;
	sprite.setRotation(degree);

	rebar.Update(position, dt);

	timer -= dt;
	if (InputMgr::GetMouseButton(Mouse::Button::Left) && !reloading)
	{
		if (timer < 0 && curClip != 0)
		{
			Shoot(Vector2f(mouseDir.x, mouseDir.y));
			curClip -= 1;
			cout << curClip << endl;
			timer = DELAY_TIME;
			if (curClip == 0)
			{
				reloading = true;
			}
		}
	}

	if (InputMgr::GetKeyUp(Keyboard::R))
	{
		reloading = true;

	}

	auto it = useBullets.begin();
	while (it != useBullets.end())
	{
		Bullet* bullet = *it;
		bullet->Update(dt);
		if (!bullet->IsActive())
		{
			it = useBullets.erase(it);
			unuseBullets.push_back(bullet);
		}
		else
		{
			++it;
		}
	}
}

bool Player::UpdateCollision(const std::list<Pickup*>& items)
{
	FloatRect bounds = sprite.getGlobalBounds();

	bool isCollided = false;
	for (auto item : items)
	{
		if (bounds.intersects(item->GetGlobalBounds()))
		{
			cout << item->GetEarnIt() << endl;

			item->GotIt();
			isCollided = true;

			/*if (item->GetType() == PickupTypes::Ammo && item->GetEarnIt())
			{
				curClip += item->GotIt();
			}*/

			switch (item->GetType())
			{
			case PickupTypes::Ammo:
				if (item->GetEarnIt())
				{
					curClip += item->GotIt();
					item->SetEarnIt();
					//curClip += 10;
					//haveAmmo += item->GotIt();
				}
				break;
			case PickupTypes::Health:
				if (item->GetEarnIt())
				{
					//health += 30;
					health += item->GotIt();
					if (health > maxHealth)
					{
						health = maxHealth;
					}
					item->SetEarnIt();

				}
				break;
			default:
				break;
			}
		}
	}
	return isCollided;
}

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	bool isCollided = false;
	for (auto bullet : useBullets)
	{
		if (bullet->UpdateCollision(zombies))
		{
			isCollided = true;
		}
	}
	return isCollided;
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets)
	{
		window.draw(bullet->GetShape());
	}
	window.draw(rebar.GetShape());
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}

	if (health < 0)
	{
		health = 0;
	}
}

int Player::GetPlayerDamage() const
{
	return playerDamamge;
}

void Player::UpgradeSpeed()
{
	speed += START_SPEED * 0.2;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2f;
}

int Player::GetHealth()
{
	return health;
}

int Player::GetMaxHealth()
{
	return maxHealth;
}

void Player::SetHealth()
{
	health += 20;
}

void Player::SetMaxHealth()
{
	maxHealth += 20;
}

void Player::SetSpeed()
{
	speed += 1000;
}

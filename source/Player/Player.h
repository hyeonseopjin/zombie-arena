#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/inputMgr.h"
#include "../Player/Bullet.h"
#include "../Player/Pickup.h"
#include "../Player/ReloadBar.h"
#include <list>
#include <cmath>

using namespace sf;

class PickUp;

class Player
{
private:
    const float START_SPEED = 1000;  // ��� ���̹�
    const float START_HEALTH = 100;
    const float START_IMMUNE_MS = 200;

    const float DELAY_TIME = 0.5f;
    const int BULLET_NUM = 50;
     int BULLETS_IN_GUN = 5;
     int PLAYER_DAMAGE = 1;

    Vector2f position;
    std::string textureFileName;
    Sprite sprite;

    Vector2i resolustion;
    IntRect arena; // �浹üũ

    int tileSize;

    Vector2f lastDir; // �������� ���� ����
    float speed;
    
    int playerDamamge; //�÷��̾� �����

    int health;
    int maxHealth;
    float immuneMs;
    bool immune;

    Time lastHit;

    const int BULLET_CACHE_SIZE = 1000;
    std::list<Bullet*> unuseBullets;
    std::list<Bullet*> useBullets;
    float distanceToMuzzle;

    ReloadBar rebar;
    int highClip;
    int curClip;
    int magazineSize;
    float delaytime;
    bool reloading;
    float timer;
    int haveAmmo;

public:
    Player();
    ~Player();

    void Shoot(Vector2f dir);

    void Spawn(IntRect arena, Vector2i res, int tileSize); // ���� �ʱ�ȭ

    bool OnHitted(Time timeHit); // �ǰݽ�

    Time GetLastTime() const;
    FloatRect GetGlobalBound() const;
    Vector2f GetPosition() const;
    float GetRotation() const; // ȸ��
    Sprite GetSprite() const;
    int GetHealth() const;

    int GetClip();
    int GetClipSum();
    void SetBul(int bul);
    void SetHiBul(int bul);
    

    void Update(float dt, IntRect arena); // deltatime
    bool UpdateCollision(const std::list<Pickup*>& items);
    bool UpdateCollision(const std::vector<Zombie*>& zombies);

    void Draw(RenderWindow& window);

    void GetHealthItem(int amount);

    int GetPlayerDamage() const;

    void UpgradeSpeed();
    void UpgradeMaxHealth();


    //���� �߰�
    int GetHealth();
    int GetMaxHealth();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Player;

enum class ZombieTypes
{
    BLOATER,
    CHASER,
    CRAWLER,
    COUNT,
};

//�������� ������ ��� �ִ� ���� ����..
struct ZombieInfo
{
    ZombieTypes type;
    std::string textureFileName;
    float speed;
    int health;
};

enum class ZombieState
{
    ALIVE,        //����
    DEATH,        //����
    DROP,        //���� ����.
};

class Zombie
{
private:
    ZombieTypes zombieTypes;
    ZombieState zombieState; //������°� ���� ����
    Vector2f position;
    Sprite sprite;
    //Sprite sprite;

    float speed;    //�⺻�ӵ�
    int health;    //ü��

    //bool alive; //��Ҵ��� �׾�����
    float deleteBloodTime;    //�Ǹ� �����ϴ� �ð�?

    static std::vector<ZombieInfo> zombieInfo;
    static bool isiInitInfo;

public:
    Zombie();
    bool OnHitted();
    bool IsAlive();

    void Spawn(float x, float y, ZombieTypes type); //�ʱ�ȭ�Լ�
    void Update(float dt, Vector2f playerPosition);

    bool UpdateCollision(Time time, Player& player);

    FloatRect GetGlobalBound();
    Sprite GetSprite();

    void Draw(RenderWindow& window);

};
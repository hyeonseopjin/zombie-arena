#include "Pickup.h"
#include "../Utils/TextureHorder.h"
#include "../Utils/Utils.h"
#include <iostream>

Pickup::Pickup() : HEALTH_START_VALUE(50), AMMO_START_VALUE(12)
{
}

Pickup::Pickup(PickupTypes type) : type(type)
{
    std::string textureID;
    switch (this->type)
    {
    case PickupTypes::Ammo:
        textureID = "graphics/ammo_pickup.png";
        value = AMMO_START_VALUE;
        break;
    case PickupTypes::Health:
        textureID = "graphics/health_pickup.png";
        value = HEALTH_START_VALUE;
        break;
    }

    sprite.setTexture(TextureHorder::GetTexture(textureID));
    Utils::SetOrigin(sprite, Pivots::CC);

    Spawn(false);
}

void Pickup::Update(float dt)
{
    timer -= dt;
    if (timer < 0.f)
    {
        Spawn(!spawned);
    }
}

void Pickup::Spawn(bool spawn)
{
    spawned = spawn;
    if (spawned)
    {
        timer = START_CECONDS_FOR_LIVE;

        int x = Utils::RandomRange(arena.left, arena.left + arena.width);
        int y = Utils::RandomRange(arena.top, arena.top + arena.height);

        sprite.setPosition(Vector2f(x, y));
        earnIt = true;
    }
    else
    {
        timer = START_WAIT_TIME;
    }
}

int Pickup::GotIt()
{

    return value;
}

void Pickup::SetArena(IntRect rect)
{
    arena = rect;
}

bool Pickup::IsSpawned()
{
    return spawned;
}

Sprite Pickup::GetSprite()
{
    return sprite;
}

FloatRect Pickup::GetGlobalBounds()
{
    return sprite.getGlobalBounds();
}

PickupTypes Pickup::GetType()
{
    return type;
}

bool Pickup::GetEarnIt() const
{
    return earnIt;
}

void Pickup::SetHealthValue()
{
    HEALTH_START_VALUE += 100;
}

void Pickup::SetAmmoValue()
{
    AMMO_START_VALUE += 20;
}

// ÀçÈÖ Ãß°¡
void Pickup::SetEarnIt()
{
    earnIt = false;
}

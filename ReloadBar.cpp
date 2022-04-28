#include "../zombie-arena-master/source/Player/ReloadBar.h"
#include "../zombie-arena-master/source/Utils/Utils.h"

ReloadBar::ReloadBar()
    :timeToReload(RELOAD_TIME), leftBullet(MAGAZINE)
{
    timebar.setSize(Vector2f(0, 0));
    timebar.setFillColor(Color::Red);
}

void ReloadBar::Update(Vector2f playerPos, float dt)
{
    timebar.setPosition(Vector2f(playerPos.x - 50, playerPos.y - 50));
    if (leftBullet == 0)
    {
        Reload(dt);
    }
}

void ReloadBar::Reload(float dt)
{
    timeToReload -= dt;
    timebar.setSize(Vector2f(timeToReload * 50, 10));
    Utils::SetOrigin(timebar, Pivots::LC);

    if (timeToReload < 0.f)
    {
        timeToReload = RELOAD_TIME;
    }
}



RectangleShape& ReloadBar::GetShape()
{
    return timebar;
}

float ReloadBar::GetBar()
{
    return timebar.getGlobalBounds().width;
}

void ReloadBar::SetBer()
{
    timeToReload = RELOAD_TIME;
}
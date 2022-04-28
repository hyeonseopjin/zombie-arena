#pragma once
#include <SFML/Graphics.hpp>
//#include "Scene.h"
// TITLE, MENU, GAME, CHARACTER

/**********************************************************
* ���� : Scene 0~4 enum class ����
***********************************************************/
enum class Scenes
{
	TITLE, MENU, GAME, CHARACTER, COUNT
};
class Scene;

class SceneMgr 
{
private:
	Scene* scenes[(int)Scenes::COUNT];

	Scenes currentScene;
public:
	void Init();
	void Release() {}
	void ChangeScene(Scenes newScene);

	void Update(float dt);
	void Draw(sf::RenderWindow* window);
};


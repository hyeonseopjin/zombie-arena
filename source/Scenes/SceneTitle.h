#pragma once
#include "Scene.h"

class SceneTitle : public Scene
{
public:
	SceneTitle(SceneMgr& mgr) : Scene(mgr) {};

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;
};


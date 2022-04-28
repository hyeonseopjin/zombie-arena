#include "SceneMgr.h"
#include "SceneTitle.h"
//#include "SceneGame.h"
//#include "SceneCharacter.h"
//#include "SceneMenu.h"
/**********************************************************
* ���� : Scene���� �ʱ�ȭ�Ѵ�.
***********************************************************/
void SceneMgr::Init()
{
	scenes[(int)Scenes::TITLE] = new SceneTitle(*this);
	//scenes[(int)Scenes::MENU] = new SceneMenu(*this);
	//scenes[(int)Scenes::CHARACTER] = new SceneCharacter(*this);
	//scenes[(int)Scenes::GAME] = new SceneGame(*this);

	scenes[(int)Scenes::TITLE]->Init();	
	//scenes[(int)Scenes::MENU]->Init();
	//scenes[(int)Scenes::CHARACTER]->Init();
	//scenes[(int)Scenes::GAME]->Init();
}
/*******************************************************************
* ���� : Scene�ϳ��ϳ��� ���������� ���ο� Scene�� �޾ƿ� �����Ѵ�.
********************************************************************/
void SceneMgr::ChangeScene(Scenes newScene)
{
	scenes[(int)currentScene]->End();
	currentScene = newScene;
	scenes[(int)currentScene]->Start();
}
/*******************************************************************
* ���� : ����� ������Ʈ �Ѵ�.
********************************************************************/
void SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
}

/*******************************************************************
* ���� : ���� ������ �׸���.
********************************************************************/
void SceneMgr::Draw(sf::RenderWindow* window)
{
	scenes[(int)currentScene]->Draw(window);
}

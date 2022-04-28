#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <map>
#include <list>

#include "../UI/UI.h"
#include "../UI/Singleton.h"


using namespace std;
using namespace sf;

class UIMgr : public Singleton<UIMgr>
{
private:
	map<std::string, UI *> UIMap;

public:
	void Init();

	UI *GetResource(std::string id);
	//Texture *GetTexture(std::string id);
	Font *GetFont(std::string id);

	
};


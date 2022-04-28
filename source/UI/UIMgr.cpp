#include "UIMgr.h"

void UIMgr::Init()
{
	Font font;
	list<UI *> loaded;	//리스트에
	loaded.push_back(new UI("MAINFONT", "fonts/zombiecontrol.ttf", font));



	for (std::list<UI *>::iterator it = loaded.begin(); it != loaded.end(); ++it)
	{
		UI *res = (*it);
		if (!res->Load())
		{
			delete res;
			// 메세지
			continue;
		}
		UIMap[(*it)->id] = res;
	}

}

UI *UIMgr::GetResource(std::string id)
{
	std::map<std::string, UI *>::iterator find = UIMap.find(id);
	if (find == UIMap.end())
	{
		return nullptr;
	}
	return find->second;
}

Font *UIMgr::GetFont(std::string id)
{
	UI *find = GetResource(id);
	if (!find)
		return nullptr;
	return find->font;
}

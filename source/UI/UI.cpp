#include "UI.h"

UI::UI()
{
	id = "";
	path = "";

	font = nullptr;
}

UI::UI(string id, string path, Font font)
{
	this->id = id;
	this->path = path;

	this->font = nullptr;
}

UI::~UI()
{
	if (!font)
		delete font;
}

bool UI::Load()
{
	font = new Font();
	return font->loadFromFile(path);
}

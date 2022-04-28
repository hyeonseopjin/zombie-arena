#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;

//Font *fontZC;
//fontZC.loadFromFile("fonts/zombiecontrol.ttf");

struct UI
{
	string id;
	string path;

	Font *font;

	UI();
	UI(string id, string path, Font font);
	~UI();

	bool Load();
};


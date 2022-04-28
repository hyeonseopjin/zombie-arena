#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHorder
{
public:
	TextureHorder();

	static Texture& GetTexture(string filename);
private:
	map<string, Texture> mapTexture;
	static TextureHorder* instance;
};


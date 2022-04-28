#include "TextureHorder.h"
#include <assert.h>

TextureHorder* TextureHorder::instance = nullptr;

TextureHorder::TextureHorder()
{
	assert(instance == nullptr);
	instance = this;
}
// 이해 필요
Texture& TextureHorder::GetTexture(string filename)
{
	// 1. filename key map에 있냐 없냐?
	// 2-1 (있다) 맵에서 찾아서 반환
	// 2-2 (없다) 만들어서 map insert

	auto& map = instance->mapTexture;

	auto it = map.find(filename);
	if (it == map.end()) // 같다는 조건
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}
	return map[filename];
}

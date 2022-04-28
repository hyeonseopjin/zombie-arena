#include "TextureHorder.h"
#include <assert.h>

TextureHorder* TextureHorder::instance = nullptr;

TextureHorder::TextureHorder()
{
	assert(instance == nullptr);
	instance = this;
}
// ���� �ʿ�
Texture& TextureHorder::GetTexture(string filename)
{
	// 1. filename key map�� �ֳ� ����?
	// 2-1 (�ִ�) �ʿ��� ã�Ƽ� ��ȯ
	// 2-2 (����) ���� map insert

	auto& map = instance->mapTexture;

	auto it = map.find(filename);
	if (it == map.end()) // ���ٴ� ����
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}
	return map[filename];
}

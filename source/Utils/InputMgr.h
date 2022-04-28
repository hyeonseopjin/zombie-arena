#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <map>


using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	list <Keyboard::Key> positiveKeys;
	list <Keyboard::Key> negativeKeys;


	float sensi; // �� ���� ũ�� ������ ����.
	float limit;
	float value; // -1.0 ~ 1.0
};

class InputMgr
{
private:
	static map <Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;

	static list<Mouse::Button> downButton;
	static list<Mouse::Button> ingButton;
	static list<Mouse::Button> upButton;

	static Vector2i mousePosition;	// ȭ�� ��ǥ�� ����
	static Vector2f mouseWorldPosition;	// ���� ��ǥ�� ����

public:
	static void Init();

	static void ClearInput();
	static void ProcessInput(const Event& event);
	static void Update(float dt, RenderWindow& window, View& worldView);


	static float GetAxis(Axis axis); // -1.0 ~ 1.0

	static int GetAxisRaw(list <Keyboard::Key> positivie, list<Keyboard::Key> negative);

	static int GetAxisRaw(Axis axis); // -1, 0, 1

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static bool GetMouseButtonDown(Mouse::Button button);
	static bool GetMouseButton(Mouse::Button button);
	static bool GetMouseButtonUp(Mouse::Button button);

	static Vector2i GetMousePosition();
	static Vector2f GetMouseWorldPosition();
};


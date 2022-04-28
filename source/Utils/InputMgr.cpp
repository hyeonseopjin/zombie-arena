#include "InputMgr.h"
#include <algorithm>
#include <cmath>

map <Axis, AxisInfo> InputMgr::mapAxis;

list<Keyboard::Key> InputMgr::downKeys;
list<Keyboard::Key> InputMgr::ingKeys;
list<Keyboard::Key> InputMgr::upKeys;

list<Mouse::Button> InputMgr::downButton;
list<Mouse::Button> InputMgr::ingButton;
list<Mouse::Button> InputMgr::upButton;

Vector2i InputMgr::mousePosition;	// 화면 좌표계 기준
Vector2f InputMgr::mouseWorldPosition;	// 월드 좌표계 기준

void InputMgr::Init()
{
	mapAxis.clear();

	AxisInfo info;

	// Horizontal
	info.axis = Axis::Horizontal;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.01f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;

	// Vertical
	info.axis = Axis::Vertical;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.01f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::S);
	info.positiveKeys.push_back(Keyboard::Down);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::W);
	info.negativeKeys.push_back(Keyboard::Up);
	mapAxis[info.axis] = info;
}

void InputMgr::ClearInput()
{
	downKeys.clear();
	upKeys.clear();
	downButton.clear();
	upButton.clear();
}

void InputMgr::ProcessInput(const Event& event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downKeys.push_back(event.key.code);
			ingKeys.push_back(event.key.code);
		}
		break;
	case Event::KeyReleased:
		ingKeys.remove(event.key.code);
		upKeys.push_back(event.key.code);
		break;
	case Event::MouseButtonPressed:
		if (!GetMouseButton(event.mouseButton.button))
		{
			downButton.push_back(event.mouseButton.button);
			ingButton.push_back(event.mouseButton.button);
		}
		break;
	case Event::MouseButtonReleased:
		ingButton.remove(event.mouseButton.button);
		upButton.push_back(event.mouseButton.button);
		break;
	default:
		break;
	}
}

void InputMgr::Update(float dt, RenderWindow& window, View& worldView)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); ++it)
	{
		AxisInfo& ref = it->second;
		// Axis
		int axis = GetAxisRaw(ref.axis);
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}

		ref.value += axis * ref.sensi * dt;
		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}
		if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	}
	mousePosition = Mouse::getPosition();
	mouseWorldPosition = window.mapPixelToCoords(mousePosition, worldView);
}

float InputMgr::GetAxis(Axis axis)
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}
	return 0.0f;
}

int InputMgr::GetAxisRaw(list<Keyboard::Key> positivie, list<Keyboard::Key> negative)
{
	int axis = 0;
	bool isPositive = false, isNegative = false;

	for (auto it = positivie.begin(); it != positivie.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}

	for (auto it = negative.begin(); it != negative.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}

	if (isPositive && isNegative)
	{
		axis = 0;
	}
	else if (isPositive)
	{
		axis = 1;
	}
	else if(isNegative)
	{
		axis = -1;
	}

	return axis;
}

int InputMgr::GetAxisRaw(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	
	return 0;
}

bool InputMgr::GetKeyDown(Keyboard::Key key)
{
	auto it = find(downKeys.begin(), downKeys.end(), key);
	return it != downKeys.end();
}

bool InputMgr::GetKey(Keyboard::Key key)
{
	auto it = find(ingKeys.begin(), ingKeys.end(), key);
	return it != ingKeys.end();
}

bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	auto it = find(upKeys.begin(), upKeys.end(), key);
	return it != upKeys.end();
}

bool InputMgr::GetMouseButtonDown(Mouse::Button button)
{
	auto it = find(downButton.begin(), downButton.end(), button);
	return it != downButton.end();
}

bool InputMgr::GetMouseButton(Mouse::Button button)
{
	auto it = find(ingButton.begin(), ingButton.end(), button);
	return it != ingButton.end();
}

bool InputMgr::GetMouseButtonUp(Mouse::Button button)
{
	auto it = find(upButton.begin(), upButton.end(), button);
	return it != upButton.end();
}

Vector2i InputMgr::GetMousePosition()
{
	//return Mouse::getPosition();
	return mousePosition;
}

Vector2f InputMgr::GetMouseWorldPosition()
{
	return mouseWorldPosition;
}

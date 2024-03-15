#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "template.h"
#include "AABBCollider.hpp"
#include "Button.hpp"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget(Surface* surface) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);

	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }

	Tmpl8::vec2 GetMousePosition() { return { mousex, mousey }; }

	bool CheckMouseCollision(const AABBCollider& object);

	Monster* CreateMonster(int typeOfMonster);

	


private:

	Surface* screen;

	
	std::vector<Monster*> monsters;
	std::vector<Button*> buttons;


	float mousex;
	float mousey;

	float time = 0.0f;
	float frameTime = 0.0f;
	int secondsPast = 0;

	Tmpl8::vec2 previousMousePos;
	Tmpl8::vec2 currentMousePos = { mousex, mousey };

	bool isLeftButtonDown = false;
	bool isRightButtonDown = false;

	Tmpl8::vec2 delta;

	int buttonState = 0;
	int prevButtonState = 0;

	Monster* currentTarget = nullptr;

	int cash = 500;

	bool sellWindowcalled = false;
	Tmpl8::Sprite* m_SellWindow = new Tmpl8::Sprite(new Tmpl8::Surface("assets/sellWindow.png"), 1);




};




}; // namespace Tmpl8
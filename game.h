#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include "Monster.hpp"
#include "template.h"
#include "AABBCollider.hpp"
#include "Button.hpp"
#include "Refiller.hpp"
#include "Window.hpp"
#include "Label.hpp"
namespace Tmpl8 {

class Surface;

enum class State
{
	startScreen,
	game,
	gameOver,

};

class Game
{
public:
	void SetTarget(Surface* surface) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);

	void StartScreen(float deltaTime);
	void GameScreen(float deltaTime);
	void GameOverScreen(float deltaTime);

	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);

	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }

	Tmpl8::vec2 GetMousePosition() { return { mousex, mousey }; }

	bool CheckMouseCollision(const AABBCollider& object);

	Monster* CreateMonster(int typeOfMonster);

	void Sell();
	void Reset();

	void DrawTile(int tx, int ty, Surface* screen, int x, int y);


private:

	State state = State::startScreen;

	Surface* screen;


	std::vector<Monster*> monsters;
	std::vector<Button*> buttons;
	std::vector<Refiller*> refillers;

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
	Monster* lastTarget = nullptr;
	Refiller* refillerTarget = nullptr;

	int cash = 500;
	int costMonster1 = 10;
	int costMonster2 = 20;
	int costMonster3 = 30;
	
	Button playButton = Button("assets/playAgainButton.tga", 2, { 350, 200 });
	Button playAgainButton = Button("assets/playAgainButton.tga", 2, { 150, 350 });

	//-----------------------------------------------------------------------------------

	Button buttonSell = Button("assets/sellButton.tga", 2, { 368, 472 });
	bool sellWindowCalled = false;
	SellWindow m_SellWindow = SellWindow("assets/sellWindow.png", 1, { 310, 166 });

	//------------------------------------------------------------------------------------

	Button buttonBuy = Button("assets/buyButton.tga", 2, { 636, 472 });
	bool buyWindowCalled = false;
	BuyWindow m_BuyWindow = BuyWindow("assets/buyWindow.png", 1, { 670, 35 });

	//------------------------------------------------------------------------------------

	bool freeze = false;

	// Text
	Label cashText = Label("cash", cash, { 5, 5 }, 0xffffff, 2);
	Label monsterText = Label("monster", monsters.size(), { 5, 20 }, 0xffffff, 2);

	Label xText = Label("x", mousex, { 5, 80 }, 0xffffff, 1);
	Label yText = Label("y", mousey, { 50, 80 }, 0xffffff, 1);

	//game over text
	Label gameOverMonsterText = Label("you Collected Monsters!", monsters.size(), { (ScreenWidth - 500) / 2, ((ScreenHeight - 25) / 2) + 50 }, 0xffffff, 4);




};




}; // namespace Tmpl8
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
	helpScreen,

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
	void HelpScreen(float deltaTime);

	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);

	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }

	Tmpl8::vec2 GetMousePosition() { return { mousex, mousey }; }

	bool CheckButtonClicked(Button button);
	bool CheckMouseCollision(const AABBCollider& object);

	Monster* CreateMonster(int typeOfMonster);

	void Sell();
	void Reset();

	void DrawTile(int tx, int ty, Surface* screen, int x, int y);


private:

	State state = State::startScreen;

	Surface* screen;

	std::vector<Monster*> monsters;
	std::vector<Refiller*> refillers;

#if _DEBUG
	std::vector<Label*>gridLabels;
#endif

	float mousex;
	float mousey;

	float time = 0.0f;
	float frameTime = 0.0f;
	float moveTime = 0.0f;
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

	int cash = 100;
	int costMonster1 = 20;
	int costMonster2 = 50;
	int costMonster3 = 100;
	
	IconLabel startScreen = IconLabel("assets/startScreen.png", 1, { 0,0 });
	IconLabel blankScreen = IconLabel("assets/blankScreen.png", 1, { 0,0 });

	//startScreen buttons
	Button playButton = Button("assets/playButton.tga", 2, { 336, 300 });
	Button helpButton = Button("assets/helpButton.tga", 2, { 368, 380 });
	Button exitButton = Button("assets/exitButton.tga", 2, { 368, 420 });

	//helpScreen buttons
	Button returnButton = Button("assets/returnButton.tga", 2, { 308,120 });

	//Game Over Buttons
	Button playAgainButton = Button("assets/playAgainButton.tga", 2, { 333, 350 });

	//game Buttons
	// sell menu buttons
	Button buttonSell = Button("assets/sellButton.tga", 2, { 368, 472 });
	bool sellWindowCalled = false;
	SellWindow m_SellWindow = SellWindow("assets/sellWindow.png", 1, { 310, 166 });

	
	// buy menu buttons
	Button buttonBuy = Button("assets/buyButton.tga", 2, { 636, 472 });
	bool buyWindowCalled = false;
	BuyWindow m_BuyWindow = BuyWindow("assets/buyWindow.png", 1, { 670, 35 });

	//exit menu
	Button buttonExit = Button("assets/backButton.tga", 2, { 10,10 });
	bool exitWindowCalled = false;
	ExitWindow m_ExitWindow = ExitWindow("assets/sellWindow.png", 1, { 310, 166 });

	//------------------------------------------------------------------------------------

	bool freeze = false;

	// Text
	Label cashText = Label("cash", cash, { 10, 480 }, 0x0, 2);
	Label monsterText = Label("Monsters Collected", monsters.size(), { (ScreenWidth - 345) / 2, 10 }, 0x0, 3);

	Label xText = Label("x", mousex, { 5, 80 }, 0xffffff, 1);
	Label yText = Label("y", mousey, { 50, 80 }, 0xffffff, 1);

};




}; // namespace Tmpl8
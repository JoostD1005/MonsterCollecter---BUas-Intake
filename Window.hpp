#pragma once

#include "Button.hpp"
#include "template.h"
#include "surface.h"
#include "IconLabel.hpp"

class Window //base class // a class for pop-up windows during game.
{
public:
	Window(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	~Window();

	Tmpl8::vec2 GetPos() const;
	Tmpl8::Sprite* GetSprite() const;

	Button GetBackButton() const;
	
	bool GetCalled() const;
	void SetCalled(bool called);
protected:
	Tmpl8::vec2 m_Pos;

	Tmpl8::Sprite* m_pSprite = nullptr;

	Button m_BackButton;

	bool m_Called = false;

};


class BuyWindow : public Window // the monster buy window that is in the game
{
public:

	BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);

	void Draw(Tmpl8::Surface* screen) const;

	Button GetMonsterButton1() const { return m_BuyMonster1; }
	Button GetMonsterButton2() const { return m_BuyMonster2; }
	Button GetMonsterButton3() const { return m_BuyMonster3; }

	IconLabel GetLock1() const { return m_Lock1; }
	IconLabel GetLock2() const { return m_Lock2; }
	IconLabel GetLock3() const { return m_Lock3; }
	

	
private:


	Button m_BuyMonster1 = Button("assets/slimeIdle.tga", 2, {700, 80});
	Button m_BuyMonster2 = Button("assets/GolemIdle.tga", 2, {700, 208});
	Button m_BuyMonster3 = Button("assets/mushroomIdle.tga", 2, {700, 336});

	IconLabel m_Lock1 = IconLabel("assets/lock.png", 1, { 700, 80 });
	IconLabel m_Lock2 = IconLabel("assets/lock.png", 1, { 700, 208 });
	IconLabel m_Lock3 = IconLabel("assets/lock.png", 1, { 700, 336 });
	
	

};


class SellWindow : public Window
{
public:

	SellWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	

	void Draw(Tmpl8::Surface* screen) const;

	Button GetSellButton() const { return m_SellButton; }

private:

	Button m_SellButton = Button("assets/sellButton.tga", 2, { 368, 297 });

};

class ExitWindow : public Window
{
public:
	ExitWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);

	void Draw(Tmpl8::Surface* screen) const;

	Button GetExitButton() const { return m_ExitButton; }
private:

	Button m_ExitButton = Button("assets/exitButton.tga", 2, { 368,250 });
};
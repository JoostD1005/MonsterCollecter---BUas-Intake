#pragma once

#include "Button.hpp"
#include "template.h"
#include "surface.h"
#include "IconLabel.hpp"

class Window
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


class BuyWindow : public Window
{
public:

	BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	

	void Draw(Tmpl8::Surface* screen) const;
	Button GetMonsterButton1() const;
	Button GetMonsterButton2() const;
	Button GetMonsterButton3() const;

	IconLabel GetLock1() const { return m_Lock1; }
	IconLabel GetLock2() const { return m_Lock2; }
	IconLabel GetLock3() const { return m_Lock3; }
	

	
private:


	Button m_BuyMonster1 = Button("assets/slimeIdle.tga", 2, {700, 80});
	Button m_BuyMonster2 = Button("assets/GolemIdle.tga", 2, {700, 208});
	Button m_BuyMonster3 = Button("assets/kingSlimeIdle.tga", 2, {700, 336});

	IconLabel m_Lock1 = IconLabel("assets/lock.png", 1, { 700, 80 });
	IconLabel m_Lock2 = IconLabel("assets/lock.png", 1, { 700, 208 });
	IconLabel m_Lock3 = IconLabel("assets/lock.png", 1, { 700, 336 });
	
	

};


class SellWindow : public Window
{
public:

	SellWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	

	void Draw(Tmpl8::Surface* screen) const;
	Button GetSellButton() const;

private:

	Button m_SellButton = Button("assets/sellButton.tga", 2, { 368, 297 });

};
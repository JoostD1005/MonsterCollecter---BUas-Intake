#pragma once

#include "Button.hpp"
#include "template.h"
#include "surface.h"


class Window
{
public:
	Window(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	~Window();

	Tmpl8::vec2 GetPos() const;
	Tmpl8::Sprite* GetSprite() const;

	Tmpl8::vec2 GetBackButtonPos() const; 
	void SetBackButtonPos();

	Button GetBackButton() const;
	
	bool GetCalled() const;
	void SetCalled(bool called);
protected:

	Button m_BackButton = Button("assets/backButton.tga", 2, GetBackButtonPos());
	bool m_Called = false;

	Tmpl8::vec2 m_Pos;
	Tmpl8::vec2 m_BackButtonPos;

	Tmpl8::Sprite* m_pSprite = nullptr;
	
};


class BuyWindow : public Window
{
public:

	BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	

	void Draw(Tmpl8::Surface* screen) const;
	Button GetMonsterButton1() const;
	Button GetMonsterButton2() const;
	Button GetMonsterButton3() const;

	
private:


	Button m_BuyMonster1 = Button("assets/slime.tga", 2, {700, 80});
	Button m_BuyMonster2 = Button("assets/Golem.tga", 2, {700, 208});
	Button m_BuyMonster3 = Button("assets/slime2.tga", 2, {700, 336});
	

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
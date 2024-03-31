#pragma once

#include "Button.hpp"
#include "template.h"
#include "surface.h"
#include "Button.hpp"


class Window
{
public:
	Window(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	~Window();

	Tmpl8::vec2 GetPos() const;
	Tmpl8::Sprite* GetSprite() const;

	Tmpl8::vec2 GetBackButtonPos(); 
	
	bool GetCalled() const;
	void SetCalled(bool called);
protected:

	Button* m_BackButton = new Button("assets/backButton.tga", 2, GetBackButtonPos());
	bool m_Called = false;

	Tmpl8::vec2 m_Pos;
	Tmpl8::Sprite* m_pSprite = nullptr;
	
};


class BuyWindow : public Window
{
public:

	BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	virtual ~BuyWindow();

	void Draw(Tmpl8::Surface* screen) const;


	
private:

	Button* m_BuyMonster1 = new Button("assets/slime.tga", 2, {700, 80});
	Button* m_BuyMonster2 = new Button("assets/Golem.tga", 2, {700, 208});
	Button* m_BuyMonster3 = new Button("assets/slime2.tga", 2, {700, 336});
	

};


class SellWindow : public Window
{
public:

	SellWindow();
	virtual ~SellWindow();

	void Draw(Tmpl8::Surface* screen) const;

private:

	Button SellButton;

};
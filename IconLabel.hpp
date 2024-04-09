#pragma once
#include "template.h"
#include "surface.h"


class IconLabel
{
public:

	IconLabel(const char* fileName, unsigned int Numframes, Tmpl8::vec2 position);
	
	Tmpl8::vec2 GetPosition() const;
	void SetPosition(Tmpl8::vec2 position);

	Tmpl8::Sprite* GetSprite() const;

	void Draw(Tmpl8::Surface* screen) const;

private:
	Tmpl8::Sprite* m_pSprite = nullptr;
	Tmpl8::vec2 m_Position;

};
#pragma once

#include "surface.h"

class Animation
{
public:
	Animation(const char* FileName, int numFrames, Tmpl8::vec2 pos);

	void DoAnimation(float deltaTime, Tmpl8::Surface* screen);

private:

	Tmpl8::Sprite* m_pSprite = nullptr;
	int m_NumFrames;
	Tmpl8::vec2 m_Pos;
	Tmpl8::vec2 M_WhereToMove;

};
#pragma once

#include "template.h"
#include "surface.h"
#include "AABBCollider.hpp"

class Refiller
{
public: 

	Refiller(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);

	Tmpl8::Sprite* GetSprite() const;
	AABBCollider GetCollider() const;

	const Tmpl8::vec2& GetOriginalPos() const;
	const Tmpl8::vec2& GetPos() const;
	void SetPos(const Tmpl8::vec2& pos);

	void Draw(Tmpl8::Surface* screen) const;


private:

	Tmpl8::Sprite* m_pSprite = nullptr;
	AABBCollider m_Collider;
	Tmpl8::vec2 m_Pos;
	Tmpl8::vec2 m_OriginalPos;





};
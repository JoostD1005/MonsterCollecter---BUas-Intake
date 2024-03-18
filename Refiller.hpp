#pragma once

#include "template.h"
#include "surface.h"
#include "AABBCollider.hpp"

class Refiller
{
public: 

	Refiller(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	~Refiller();

	Tmpl8::Sprite* GetSprite() const;
	AABBCollider GetCollider() const;

	const Tmpl8::vec2& GetPos() const;
	void SetPos(const Tmpl8::vec2& pos);




private:

	Tmpl8::Sprite* m_pSprite = nullptr;
	AABBCollider collider;
	Tmpl8::vec2 pos;





};
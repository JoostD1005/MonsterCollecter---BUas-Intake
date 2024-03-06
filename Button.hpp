#pragma once

#include "template.h"
#include "surface.h"
#include "AABBCollider.hpp"


class Button
{
public:

	Button(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos);
	~Button();

	Tmpl8::Sprite* GetSprite() const;
	const Tmpl8::vec2& GetPosition() const;
	AABBCollider GetCollider() const;



	void SetSprite(Tmpl8::Sprite* sprite);

	void SetPosition(const Tmpl8::vec2& pos);

	void SetCollider(const AABBCollider collider);

	void SetFrameNum(unsigned int frameNum);

	void Draw(Tmpl8::Surface* screen) const;




private:

	Tmpl8::vec2 m_Position;
	Tmpl8::Sprite* m_pSprite = nullptr;
	AABBCollider m_Collider;


};
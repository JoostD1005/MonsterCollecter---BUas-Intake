
#pragma once

#include "template.h"


class AABBCollider
{
public:

	AABBCollider(Tmpl8::vec2 position = {400,200}, int width = 0, int height = 0);



	int GetWidth() const;
	int GetHeight() const;

	Tmpl8::vec2 GetPosition() const;
	Tmpl8::vec2 GetHalfSize();

	void SetPosition(Tmpl8::vec2 position);

	void SetSize(int width, int height);
	

	bool CheckCollision(AABBCollider& other);

	



private:

	int m_Height;
	int m_Width;

	Tmpl8::vec2 m_Position { 400.0f, 200.0f };
	
};
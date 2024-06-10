#pragma once

#include "template.h"


//inspo: https://www.youtube.com/watch?v=l2iCYCLi6MU

class AABBCollider //basic collision detection using Axis-Aligned Bounding Boxxes.
{
public:
	AABBCollider() = default;
	AABBCollider(const Tmpl8::vec2& position, const Tmpl8::vec2& size);

	float GetWidth() const;
	float GetHeight() const;

	const Tmpl8::vec2& GetPosition() const;
	Tmpl8::vec2 GetHalfSize() const;

	void SetPosition(const Tmpl8::vec2& position);

	void SetSize(float width, float height);

	bool CheckCollision(const AABBCollider& other) const;

private:
    Tmpl8::vec2 m_Size{ 0.0f };
	Tmpl8::vec2 m_Position { 0.0f };
};
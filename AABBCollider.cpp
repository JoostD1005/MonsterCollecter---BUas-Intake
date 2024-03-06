#include "AABBCollider.hpp"

AABBCollider::AABBCollider(const Tmpl8::vec2& position, const Tmpl8::vec2& size)
{
	m_Position = position;
	m_Size = size;
}

float AABBCollider::GetWidth() const
{
	return m_Size.x;
}

float AABBCollider::GetHeight() const
{
	return m_Size.y;
}

const Tmpl8::vec2& AABBCollider::GetPosition() const
{
	return m_Position;
}

Tmpl8::vec2 AABBCollider::GetHalfSize() const
{
	return m_Size * 0.5f;
}

void AABBCollider::SetPosition(const Tmpl8::vec2& position)
{
	m_Position = position;
}

void AABBCollider::SetSize(float width, float height)
{
	m_Size.x = width;
	m_Size.y = height;
}

bool AABBCollider::CheckCollision(const AABBCollider& other) const
{
	Tmpl8::vec2 otherPosition = other.GetPosition();
	Tmpl8::vec2 otherHalfSize = other.GetHalfSize();

	Tmpl8::vec2 thisPosition = GetPosition();
	Tmpl8::vec2 thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	return (intersectX < 0.0f || intersectY < 0.0f);
}



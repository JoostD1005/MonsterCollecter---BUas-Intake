
#include "AABBCollider.hpp"







AABBCollider::AABBCollider(Tmpl8::vec2 position, int width, int height)
{
	m_Position = position;
	m_Width = width;
	m_Height = height;
}



int AABBCollider::GetWidth()
{
	return m_Width;
}

int AABBCollider::GetHeight()
{
	return m_Height;
}

Tmpl8::vec2 AABBCollider::GetPosition() const
{
	return m_Position;
}




Tmpl8::vec2 AABBCollider::GetHalfSize()
{
	Tmpl8::vec2 halfSize = { static_cast<float>(m_Width / 2), static_cast<float>(m_Height / 2) };

	return halfSize;
}





void AABBCollider::SetPosition(Tmpl8::vec2 position)
{
	m_Position = position;
}



void AABBCollider::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}










bool AABBCollider::CheckCollision(AABBCollider& other)
{
	Tmpl8::vec2 otherPosition = other.GetPosition();
	Tmpl8::vec2 otherHalfSize = other.GetHalfSize();

	Tmpl8::vec2 thisPosition = GetPosition();
	Tmpl8::vec2 thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f || intersectY < 0.0f)
	{
		return true;
	}

		return false;
}



#include "IconLabel.hpp"

IconLabel::IconLabel(const char* fileName, unsigned int numFrames, Tmpl8::vec2 position) :
	m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{
	SetPosition(position);
}

Tmpl8::vec2 IconLabel::GetPosition() const
{
	return m_Position;
}

void IconLabel::SetPosition(Tmpl8::vec2 position)
{
	m_Position = position;
}

Tmpl8::Sprite* IconLabel::GetSprite() const
{
	return m_pSprite;
}

void IconLabel::Draw(Tmpl8::Surface* screen) const
{
	if (m_pSprite != nullptr)
	{
		const auto pos = m_Position;
		m_pSprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}

#include "Button.hpp"

//Constructor and Destructor.



Button::Button(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
	m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{
	SetPosition(pos);
	m_Collider.SetSize( static_cast<float>( m_pSprite->GetWidth() ), static_cast<float>( m_pSprite->GetHeight() ) );
}

Button::~Button()
{
}




const Tmpl8::vec2& Button::GetPosition() const
{
	return m_Collider.GetPosition();
}


AABBCollider Button::GetCollider() const
{
	return m_Collider;
}


Tmpl8::Sprite* Button::GetSprite() const
{
	return m_pSprite;
}

void Button::SetCollider(const AABBCollider collider)
{
	m_Collider = collider;
}

void Button::Draw(Tmpl8::Surface* screen) const
{
	if (m_pSprite != nullptr)
	{
		const auto pos = m_Collider.GetPosition();
		m_pSprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}






void Button::SetPosition(const Tmpl8::vec2& pos)
{
	m_Collider.SetPosition(pos);
}


void Button::SetSprite(Tmpl8::Sprite* sprite)
{
	m_pSprite = sprite;
}

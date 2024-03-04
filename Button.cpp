#include "Button.hpp"

//Constructor and Destructor.



Button::Button(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
	m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{
	SetPosition(pos);
	m_Collider.SetSize(m_pSprite->GetWidth(), m_pSprite->GetHeight());
}

Button::~Button()
{
	delete m_pSprite;
	m_pSprite = 0;
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






void Button::SetPosition(const Tmpl8::vec2& pos)
{
	m_Collider.SetPosition(pos);
}


void Button::SetSprite(Tmpl8::Sprite* sprite)
{
	m_pSprite = sprite;
}

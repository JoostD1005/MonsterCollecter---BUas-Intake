#include "Refiller.hpp"


Refiller::Refiller(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_Pos(pos),
    m_OriginalPos(pos)

{
    m_Collider.SetSize(static_cast<float>(m_pSprite->GetWidth()), static_cast<float>(m_pSprite->GetHeight()));
    m_Collider.SetPosition(pos);
}

Tmpl8::Sprite* Refiller::GetSprite() const
{
    return m_pSprite;
}

AABBCollider Refiller::GetCollider() const
{
    return m_Collider;
}

const Tmpl8::vec2& Refiller::GetOriginalPos() const
{
    return m_OriginalPos;
}

const Tmpl8::vec2& Refiller::GetPos() const
{
    return m_Pos;
}

void Refiller::SetPos(const Tmpl8::vec2& pos)
{
    m_Collider.SetPosition(pos); \
        m_Pos = pos;
}

void Refiller::Draw(Tmpl8::Surface* screen) const
{
    m_pSprite->Draw(screen, m_Pos.x, m_Pos.y);
}


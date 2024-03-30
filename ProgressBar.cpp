#include "ProgressBar.hpp"

Tmpl8::Sprite* ProgressBar::GetSprite() const
{
    return m_BackgroundBar;
}

const Tmpl8::vec2& ProgressBar::GetPos() const
{
    return m_Pos;
}

void ProgressBar::Draw(Tmpl8::Surface* screen) const
{
    m_BackgroundBar->Draw(screen, static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y));
    float width = 58.0f * m_Value;
    screen->Bar(m_Pos.x + 3.0f, m_Pos.y + 3.0f, m_Pos.x + 3.0f + width, m_Pos.y + 5.0f, m_Color);
}


void ProgressBar::SetPos(const Tmpl8::vec2& pos) //redo without the reference. maybe do this in monster or game file?
{
    m_Pos = pos;
}

float ProgressBar::GetWidth() const
{
    return static_cast<float>(m_BackgroundBar->GetWidth());
}

float ProgressBar::GetHeight() const
{
    return static_cast<float>(m_BackgroundBar->GetHeight());
}

Tmpl8::Pixel ProgressBar::GetColour() const
{
    return m_Color;
}

void ProgressBar::SetColour(Tmpl8::Pixel colour)
{
    m_Color = colour;
}

float ProgressBar::GetValue() const
{
    return m_Value;
}

void ProgressBar::SetValue(float value)
{
    m_Value = value;
}




#include "Window.hpp"

Window::Window(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    m_Pos(pos),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{
}

Tmpl8::vec2 Window::GetPos() const
{
    return m_Pos;
}

Tmpl8::Sprite* Window::GetSprite() const
{
    return m_pSprite;
}

Tmpl8::vec2 Window::GetBackButtonPos()
{
    return { GetPos().x + GetSprite()->GetWidth() - 10, GetPos().y + GetSprite()->GetHeight() - 10 };
}

bool Window::GetCalled() const
{
    return m_Called;
}

void Window::SetCalled(bool called)
{
    m_Called = called;
}

//--------------------------------------------------------------------------------------------

BuyWindow::BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    m_Pos(pos),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{
}

#include "Window.hpp"

Tmpl8::vec2 Window::GetPos() const
{
    return m_Pos;
}

bool Window::GetCalled() const
{
    return m_Called;
}

void Window::SetCalled(bool called)
{
    m_Called = called;
}

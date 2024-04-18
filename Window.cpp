#include "Window.hpp"

Window::Window(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    m_Pos(pos),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_BackButton("assets/backButton.tga", 2)
{
    m_BackButton.SetPosition({ m_Pos.x + m_pSprite->GetWidth() - 47, m_Pos.y + 15 });
}

Window::~Window()
{
    delete m_pSprite;
    m_pSprite = nullptr;
}

Tmpl8::vec2 Window::GetPos() const
{
    return m_Pos;
}

Tmpl8::Sprite* Window::GetSprite() const
{
    return m_pSprite;
}



Button Window::GetBackButton() const
{
    return m_BackButton;
}

bool Window::GetCalled() const
{
    return m_Called;
}

void Window::SetCalled(bool called)
{
    m_Called = called;
}

//----------------class BuyWindow : public Window--------------------------------------------------------

BuyWindow::BuyWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    Window(fileName, numFrames, pos)
{
  //  SetBackButtonPos();
}

void BuyWindow::Draw(Tmpl8::Surface* screen) const
{
    m_pSprite->Draw(screen, m_Pos.x, m_Pos.y);
    m_BuyMonster1.Draw(screen);
    m_BuyMonster2.Draw(screen);
    m_BuyMonster3.Draw(screen);
    m_BackButton.Draw(screen);
  

    screen->Print("cost: 10", 700, 144, 0x000000);
    screen->Print("cost: 25", 700, 272, 0x000000);
    screen->Print("cost: 50", 700, 400, 0x000000);
}

Button BuyWindow::GetMonsterButton1() const
{
    return m_BuyMonster1;
}

Button BuyWindow::GetMonsterButton2() const
{
    return m_BuyMonster2;
}

Button BuyWindow::GetMonsterButton3() const
{
    return m_BuyMonster3;
}




//----------------class SellWindow : public Window------------------------------------------------------------------

SellWindow::SellWindow(const char* fileName, unsigned int numFrames, Tmpl8::vec2 pos) :
    Window(fileName, numFrames, pos)
{
  //  SetBackButtonPos();
}


void SellWindow::Draw(Tmpl8::Surface* screen) const
{
    m_pSprite->Draw(screen, m_Pos.x, m_Pos.y);
    m_SellButton.Draw(screen);
    m_BackButton.Draw(screen);
    
}

Button SellWindow::GetSellButton() const
{
    return m_SellButton;
}

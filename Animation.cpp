#include "Animation.hpp"

Animation::Animation(const char* fileName, int numFrames, Tmpl8::vec2 pos) :
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_NumFrames(numFrames),
    m_Pos(pos)
{
}

void Animation::DoAnimation(float deltaTime, Tmpl8::Surface* screen)
{
    float frameTime = 0.0f;
    frameTime = frameTime + deltaTime;
    if (frameTime > 0.25f)
    {
     
       int i = 0;
       if (m_pSprite->GetFrame() < m_NumFrames - 1)
            {
                m_pSprite->SetFrame(i + 1);
            }
       frameTime = 0.0f;
    }
    if (m_pSprite->GetFrame() == m_NumFrames)
    {
        m_pSprite->SetFrame(0);
    }
    m_pSprite->Draw(screen, m_Pos.x, m_Pos.y);
}

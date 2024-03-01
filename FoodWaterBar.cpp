#include "FoodWaterBar.hpp"

Tmpl8::Sprite* FoodWaterBar::GetSprite()
{
    return m_BackgroundBar;
}

Tmpl8::vec2 FoodWaterBar::GetPos()
{
    return m_Pos;
}

void FoodWaterBar::SetPos(Tmpl8::vec2 pos) //redo without the reference. maybe do this in monster or game file?
{
    m_Pos = pos;
}
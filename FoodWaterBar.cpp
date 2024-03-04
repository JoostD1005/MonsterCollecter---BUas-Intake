#include "FoodWaterBar.hpp"

Tmpl8::Sprite* FoodWaterBar::GetSprite() const
{
    return m_BackgroundBar;
}

Tmpl8::vec2 FoodWaterBar::GetPos() const
{
    return m_Pos;
}

Tmpl8::vec2 FoodWaterBar::GetFillingPos1() const
{
   
    return m_Pos + Tmpl8::vec2 {4, 4};
}

Tmpl8::vec2 FoodWaterBar::GetFillingPos2() const
{
   
    return  GetFillingPos1() + Tmpl8::vec2{60, 2};
}


void FoodWaterBar::SetPos(Tmpl8::vec2 pos) //redo without the reference. maybe do this in monster or game file?
{
    m_Pos = pos;
}




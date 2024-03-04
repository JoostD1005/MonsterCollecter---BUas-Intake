#pragma once

#include "template.h"
#include "surface.h"


class FoodWaterBar 
{
public:

	/*deplete Bar;
	replennish Bar;*/

	Tmpl8::Sprite* GetSprite() const;

	Tmpl8::vec2 GetPos() const;

	void SetPos(Tmpl8::vec2 pos);
	
	Tmpl8::vec2 GetFillingPos1() const;
	Tmpl8::vec2 GetFillingPos2() const;




private:


	Tmpl8::Sprite* m_BackgroundBar = new Tmpl8::Sprite(new Tmpl8::Surface("assets/bar.png"), 1);

	/*depledingBar;*/

	Tmpl8::vec2 m_Pos;

	


};
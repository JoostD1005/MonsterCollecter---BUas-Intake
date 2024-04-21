#pragma once

#include "template.h"
#include "surface.h"


class ProgressBar // a bar that can be filled up and decrease. 
{
public:

	Tmpl8::Sprite* GetSprite() const;

	const Tmpl8::vec2& GetPos() const;
	void SetPos(const Tmpl8::vec2& pos);

	float GetWidth() const;
	float GetHeight() const;

	Tmpl8::Pixel GetColour() const;
	void SetColour(Tmpl8::Pixel colour);

	float GetValue() const;

	// Set the value of the food/water bar.
	// 1.0f == full, 0.0f == empty.
	void SetValue(float value);

	void Draw(Tmpl8::Surface* screen) const;

private:
	Tmpl8::Sprite* m_BackgroundBar = new Tmpl8::Sprite(new Tmpl8::Surface("assets/bar.png"), 1);

	Tmpl8::vec2 m_Pos{0};
	Tmpl8::Pixel m_Color{0};

	// Percentage of bar.
	float m_Value = 1.0f;
};
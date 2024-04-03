#pragma once
#include "surface.h"
#include <string_view>
#include <string>

class Label
{
public:

	Label(std::string_view a_String, float value, Tmpl8::vec2 pos, Tmpl8::Pixel color, int width);

	void Print(Tmpl8::Surface* screen);

	void SetValue(float value) { m_Value = value;  }
	void SetPos(Tmpl8::vec2 pos) { m_Pos = pos; }
	void SetWidth(int width) { m_Width = width; }
	void SetColor(Tmpl8::Pixel color) { m_Color = color; }

private:

	std::string m_String;
	float m_Value = 0;
	Tmpl8::vec2 m_Pos;
	Tmpl8::Pixel m_Color;
	int m_Width;


};
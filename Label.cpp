#include "Label.hpp"
#include <iostream>
#include <format>

Label::Label(std::string_view a_String, float value, Tmpl8::vec2 pos, Tmpl8::Pixel color, int width) :
	m_String(a_String),
	m_Value(value),
	m_Pos(pos),
	m_Color(color),
	m_Width(width)
{

}

void Label::Print(Tmpl8::Surface* screen)
{
	 // format the string to take a changing value
	screen->Print(std::format("{}: {}", m_String, m_Value), m_Pos.x, m_Pos.y, m_Color, m_Width);
}

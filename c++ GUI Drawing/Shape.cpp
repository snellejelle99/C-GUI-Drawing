#include "Shape.h"

Shape::Shape(double left, double top, Windows::UI::Color color) : left(left), top(top), color(color)
{
	
}

Shape::~Shape()
{
}

Windows::UI::Color Shape::GetColor()
{
	return color;
}

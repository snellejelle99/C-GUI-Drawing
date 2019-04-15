#include "Shape.h"
#include <algorithm>

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

void Shape::AddSubShape(Shape * subShape)
{
	subShapes.push_back(subShape);
}

void Shape::DelSubShape(Shape * subShape)
{
	for (Shape* s : subShapes)
	{
		if (s == subShape)
		{
			subShapes.erase(std::remove(subShapes.begin(), subShapes.end(), s), subShapes.end());
		}
	}
}

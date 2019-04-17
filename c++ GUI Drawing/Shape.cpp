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
	subShape->AddParent(this);
}

void Shape::DelSubShape(Shape * subShape)
{
	for (Shape* s : subShapes)
	{
		if (s == subShape)
		{
			subShapes.erase(std::remove(subShapes.begin(), subShapes.end(), s), subShapes.end());
			return;
		}
	}
}

//return a list containing every shape beneath this shape recursively
const std::vector<Shape*> Shape::GetSubShapes()
{
	std::vector<Shape*> result;
	if (subShapes.size() == 0) return result;
	else 
	{
		for (Shape* sh : subShapes)
		{
			result.push_back(sh);
			std::vector<Shape*> addition = sh->GetSubShapes();
			result.insert(result.end(), addition.begin(), addition.end());
		}
	}

	return result;
}

void Shape::AddParent(Shape * pShape)
{
	if (std::find(parentShapes.begin(), parentShapes.end(), pShape) == parentShapes.end()) //if not found add to parentShapes
	{
		parentShapes.push_back(pShape);
	}
}

void Shape::DellFromParent()
{
	for (Shape* ps : parentShapes)
	{
		ps->DelSubShape(this);
	}
}

const std::vector<Shape*> Shape::GetParentShapes()
{
	return parentShapes;
}

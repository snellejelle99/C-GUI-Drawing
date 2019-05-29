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

bool Shape::AddSubShape(Shape * subShape)
{
	if (!CheckIfParent(subShape))
	{
		subShapes.push_back(subShape);
		bool succes = subShape->AddParent(this);
		if (succes) return true;
		else return false;
	}
	return false;
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

std::vector<double> Shape::getTopLeft()
{
	std::vector<double> tl;
	tl.push_back(left);
	tl.push_back(top);
	return tl;
}

void Shape::setTopLeft(double left, double top)
{
	this->left = left;
	this->top = top;
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

//return a list containing every shape above this shape recursively
bool Shape::CheckIfParent(Shape* shape) 
{
	if (std::find(parentShapes.begin(), parentShapes.end(), shape) == parentShapes.end())
	{
		for (Shape* sh : parentShapes)
		{
			if (sh->CheckIfParent(shape))
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

bool Shape::CheckIfSubShape(Shape* shape)
{
	if (std::find(subShapes.begin(), subShapes.end(), shape) == subShapes.end())
	{
		for (Shape* sh : parentShapes)
		{
			if (sh->CheckIfSubShape(shape))
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

bool Shape::AddParent(Shape * pShape)
{
	if (!CheckIfSubShape(pShape))
	{
		if (std::find(parentShapes.begin(), parentShapes.end(), pShape) == parentShapes.end()) //if not found add to parentShapes
		{
			parentShapes.push_back(pShape);
			return true;
		}
	}
	return false;
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

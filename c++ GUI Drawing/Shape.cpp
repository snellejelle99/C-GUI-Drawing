#include "Shape.h"
#include <algorithm>

Shape::Shape(double left, double top, Windows::UI::Color color) : left(left), top(top), color(color)
{

}

Shape::~Shape()
{
}

//gets the color of the shape
Windows::UI::Color Shape::GetColor()
{
	return color;
}

//add the given shape to the subshape list, returns true if succesfull
bool Shape::AddSubShape(Shape * subShape)
{
	if (!CheckIfParent(subShape))
	{		
		//subShapes.push_back(subShape);
		bool succes = subShape->AddParent(this);
		if (succes) { 
			subShapes.push_back(subShape);
			return true; 
		}
		else return false;
	}
	return false;
}

//delete the given shape from the subshape's list of this shape
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

//get the values for the left and top margin
std::vector<double> Shape::getTopLeft()
{
	std::vector<double> tl;
	tl.push_back(left);
	tl.push_back(top);
	return tl;
}

//set the values for the left and top margin
void Shape::setTopLeft(double left, double top)
{
	this->left = left;
	this->top = top;
}

//return a list containing every shape beneath this shape recursively
const std::vector<Shape*> Shape::GetSubShapes()
{
	std::vector<Shape*> result;
	if (subShapes.size() == 0) return result; //stop condition
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

//get a list with every shape above this shape recursively
const std::vector<Shape*> Shape::GetAllParents()
{
	std::vector<Shape*> result;
	if (parentShapes.size() == 0) return result; //stop condition
	else
	{
		for (Shape* sh : parentShapes)
		{
			result.push_back(sh);
			std::vector<Shape*> addition = sh->GetAllParents();
			result.insert(result.end(), addition.begin(), addition.end());
		}
	}

	return result;
}

//check if the given shape is already a parent shape above this shape recursively
bool Shape::CheckIfParent(Shape* shape) 
{
	if (std::find(parentShapes.begin(), parentShapes.end(), shape) == parentShapes.end()) //if it is not a direct parent then check all the parents above this shape.
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
	return false;
}

//check if the provided shape is in the subshape list or in the subshape list of this shape's subshapes.
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
	return false;
}

//adds a parent(provided as parameter) to the shape, returns true if succesfull
bool Shape::AddParent(Shape * pShape)
{
	if (!CheckIfSubShape(pShape)) //check if the possible parent is already a subshape
	{
		if (std::find(parentShapes.begin(), parentShapes.end(), pShape) == parentShapes.end()) //check if it is already a parent
		{
			if (parentShapes.size() == 0) //check if there are no other parents
			{
				parentShapes.push_back(pShape); //add to parents list
				return true;
			}
		}
		else if (*std::find(parentShapes.begin(), parentShapes.end(), pShape) == pShape) // check if parent already exists in this shape and return true if so
		{
			return true;
		}
	}
	return false;
}

//delete this shape from its parentshapes
void Shape::DellFromParent()
{
	for (Shape* ps : parentShapes)
	{
		ps->DelSubShape(this);
	}
}

//get a list with parentshapes
const std::vector<Shape*> Shape::GetParentShapes()
{
	return parentShapes;
}

#include "GroupCommand.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <algorithm>

GroupCommand::GroupCommand(Shape* shape, Shape* subShape, std::vector<Shape*> &shapes) : shape(shape), subShape(subShape), shapes(shapes)
{
}

GroupCommand::~GroupCommand()
{
}

//execute that groups an element to another element and removes it from the toplevel shapes list
void GroupCommand::Execute()
{
	if (subShape != shape)
	{
		bool succes = shape->AddSubShape(subShape);
		if (succes)
		{
			shapes.erase(remove(shapes.begin(), shapes.end(), subShape), shapes.end());
			executed = true;
		}
	}
}

//undo that removes the subshape from the parent element and returns it to the toplevel shapes list
void GroupCommand::Undo()
{
	if (executed) 
	{
		shape->DelSubShape(subShape);
		shapes.push_back(subShape);
	}
}
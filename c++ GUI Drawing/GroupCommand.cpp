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

void GroupCommand::Execute()
{
	if (subShape != shape)
	{
		shape->AddSubShape(subShape);
		shapes.erase(remove(shapes.begin(), shapes.end(), shape), shapes.end());
	}
}

void GroupCommand::Undo()
{
	shape->DelSubShape(subShape);
	shapes.push_back(subShape);
}
#include "GroupCommand.h"
#include "Rectangle.h"
#include "Ellipse.h"

GroupCommand::GroupCommand(Shape* shape, Shape* subShape) : shape(shape), subShape(subShape)
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
	}
}

void GroupCommand::Undo()
{
	shape->DelSubShape(subShape);
}
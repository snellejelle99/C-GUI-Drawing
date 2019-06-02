#include "ChangeColorCommand.h"

//constructor
ChangeColorCommand::ChangeColorCommand(Shape* shape, Windows::UI::Color newColor) : shape(shape), newColor(newColor), oldColor(shape->GetColor())
{
}

ChangeColorCommand::~ChangeColorCommand()
{
}

//execute that changes the color of the shape
void ChangeColorCommand::Execute()
{
	shape->ChangeColor(newColor);
}

//undo that changes the color back
void ChangeColorCommand::Undo()
{
	shape->ChangeColor(oldColor);
}

#include "ChangeColorCommand.h"



ChangeColorCommand::ChangeColorCommand(Shape & shape, Windows::UI::Color newColor) : shape(shape), newColor(newColor), oldColor(shape.GetColor())
{
}


ChangeColorCommand::~ChangeColorCommand()
{
}

void ChangeColorCommand::Execute()
{
	shape.ChangeColor(newColor);
}

void ChangeColorCommand::Undo()
{
	shape.ChangeColor(oldColor);
}

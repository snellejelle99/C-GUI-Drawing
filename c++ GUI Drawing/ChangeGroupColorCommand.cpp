#include "ChangeGroupColorCommand.h"

ChangeGroupColorCommand::ChangeGroupColorCommand(Shape* shape, Windows::UI::Color newColor) : shape(shape), newColor(newColor), oldColor(shape->GetColor())
{
}

ChangeGroupColorCommand::~ChangeGroupColorCommand()
{
}

void ChangeGroupColorCommand::Execute()
{
	shape->ChangeColor(newColor);
}

void ChangeGroupColorCommand::Undo()
{
	shape->ChangeColor(oldColor);
}
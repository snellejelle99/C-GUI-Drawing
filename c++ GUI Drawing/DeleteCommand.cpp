#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Windows::UI::Xaml::Shapes::Shape^ shape) : canvas(canvas), shape(shape)
{
}

DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::Execute()
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape, &index);
	canvas->Children->RemoveAt(index);
}

void DeleteCommand::Undo()
{
	canvas->Children->Append(shape);
}

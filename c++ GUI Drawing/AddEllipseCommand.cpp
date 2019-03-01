#include "AddEllipseCommand.h"

AddEllipseCommand::AddEllipseCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, std::vector<Shape*> &shapes, Windows::UI::Xaml::Shapes::Ellipse ^ellip, Windows::UI::Color color) : canvas(canvas), color(color), ellip(ellip)
{
	double left = canvas->GetLeft(ellip);
	double top = canvas->GetTop(ellip);
	shape = new Ellipse(left, top, color, ellip);
	shapes.push_back(shape);
}

AddEllipseCommand::~AddEllipseCommand()
{
}

void AddEllipseCommand::Execute()
{
	if (isExecuted) canvas->Children->Append(ellip);
	else isExecuted = true;
}

void AddEllipseCommand::Undo()
{
	unsigned int index = 0;
	canvas->Children->IndexOf(ellip, &index);
	canvas->Children->RemoveAt(index);
}

#include "AddEllipseCommand.h"
#include "Ellipse.h"	
#include <algorithm>

//constructor that takes a wpf ellipse element and creates a Ellipse object which is pushed to the main shapes list.
AddEllipseCommand::AddEllipseCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, std::vector<Shape*> &shapes, Windows::UI::Xaml::Shapes::Ellipse ^ellip, Windows::UI::Color color) : canvas(canvas), color(color), ellip(ellip), shapes(shapes)
{
	double left = canvas->GetLeft(ellip);
	double top = canvas->GetTop(ellip);
	shape = new Ellipse(left, top, color, ellip);
	shapes.push_back(shape);
}

AddEllipseCommand::~AddEllipseCommand()
{
}

//execute that appends the ellipse to the canvas.
void AddEllipseCommand::Execute()
{
	if (isExecuted) canvas->Children->Append(ellip);
	else isExecuted = true;
}

//undo that removes the wpf element from the canvas and removes the shape from the main shapes list
void AddEllipseCommand::Undo()
{
	unsigned int index = 0;
	canvas->Children->IndexOf(ellip, &index);
	canvas->Children->RemoveAt(index);
	shapes.erase(remove(shapes.begin(), shapes.end(), shape), shapes.end());
}

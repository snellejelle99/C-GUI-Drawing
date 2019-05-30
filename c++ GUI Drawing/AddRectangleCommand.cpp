#include "AddRectangleCommand.h"
#include "Rectangle.h"
#include <algorithm>

//constructor that takes a wpf rectangle element and creates a Rectangle object which is pushed to the main shapes list.
AddRectangleCommand::AddRectangleCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, std::vector<Shape*> &shapes, Windows::UI::Xaml::Shapes::Rectangle ^rect, Windows::UI::Color color) : canvas(canvas), color(color), rect(rect), shapes(shapes)
{
	double left = canvas->GetLeft(rect);
	double top = canvas->GetTop(rect);
	shape = new Rectangle(left, top, color, rect);
	shapes.push_back(shape);
}

AddRectangleCommand::~AddRectangleCommand()
{

}

//execute that appends the rectangle to the canvas.
void AddRectangleCommand::Execute()
{
	if (isExecuted) canvas->Children->Append(rect);
	else isExecuted = true;
}

//undo that removes the wpf element from the canvas and removes the shape from the main shapes list
void AddRectangleCommand::Undo()
{
	unsigned int index = 0;
	canvas->Children->IndexOf(rect, &index);
	canvas->Children->RemoveAt(index);
	shapes.erase(remove(shapes.begin(), shapes.end(), shape), shapes.end());
}


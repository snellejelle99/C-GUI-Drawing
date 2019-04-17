#include "AddRectangleCommand.h"
#include "Rectangle.h"
#include <algorithm>

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

void AddRectangleCommand::Execute()
{
	if (isExecuted) canvas->Children->Append(rect);
	else isExecuted = true;
}

void AddRectangleCommand::Undo()
{
	unsigned int index = 0;
	canvas->Children->IndexOf(rect, &index);
	canvas->Children->RemoveAt(index);
	shapes.erase(remove(shapes.begin(), shapes.end(), shape), shapes.end());
}


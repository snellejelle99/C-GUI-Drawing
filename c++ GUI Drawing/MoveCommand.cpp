#include "MoveCommand.h"
#include "Rectangle.h"
#include "Ellipse.h"

MoveCommand::MoveCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop) : canvas(canvas), shape(shape), newLeft(newLeft), newTop(newTop)
{
	std::vector<double> topleft = shape->getTopLeft();
	oldLeft = topleft[0];
	oldTop = topleft[1];
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	shape->setTopLeft(newLeft - shape->GetShape()->Width / 2, newTop - shape->GetShape()->Height / 2);

	canvas->SetLeft(shape->GetShape(), newLeft - shape->GetShape()->Width/2);
	canvas->SetTop(shape->GetShape(), newTop - shape->GetShape()->Height / 2);
	//Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	//Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	//if (rectShape) rectShape->Accept(shapeDeleteVisitor);
	//else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
}

void MoveCommand::Undo()
{
	canvas->SetLeft(shape->GetShape(), oldLeft);
	canvas->SetTop(shape->GetShape(), oldTop);
	//Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	//Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	//if (rectShape) rectShape->Accept(shapeAddVisitor);
	//else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
}

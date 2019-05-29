#include "MoveCommand.h"
#include "Rectangle.h"
#include "Ellipse.h"

MoveCommand::MoveCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop) : canvas(canvas), shape(shape), newLeft(newLeft), newTop(newTop)
{
	std::vector<double> topleft = shape->getTopLeft();
	oldLeft = topleft[0];
	oldTop = topleft[1];
	leftFactor = (newLeft - shape->GetShape()->Width/2) - topleft[0];
	topFactor =  (newTop - shape->GetShape()->Height/2) - topleft[1];
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	shape->setTopLeft(oldLeft + leftFactor, oldTop + topFactor);

	canvas->SetLeft(shape->GetShape(), oldLeft + leftFactor);
	canvas->SetTop(shape->GetShape(), oldTop + topFactor);
	//Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	//Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	//if (rectShape) rectShape->Accept(shapeDeleteVisitor);
	//else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
}

void MoveCommand::Undo()
{
	shape->setTopLeft(oldLeft, oldTop);

	canvas->SetLeft(shape->GetShape(), oldLeft);
	canvas->SetTop(shape->GetShape(), oldTop);




	/*std::vector<double> topleft = shape->getTopLeft();
	shape->setTopLeft(topleft[0] - leftFactor, topleft[1] - topFactor);

	canvas->SetLeft(shape->GetShape(), topleft[0] - leftFactor);
	canvas->SetTop(shape->GetShape(), topleft[1] - topFactor);*/

	//Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	//Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	//if (rectShape) rectShape->Accept(shapeAddVisitor);
	//else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
}

#include "MoveGroupCommand.h"
#include "MoveGroupVisitor.h"
#include "MoveGroupBackVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

//execute that calculates the left and topfactor for the move
MoveGroupCommand::MoveGroupCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop) : canvas(canvas), shape(shape)
{
	std::vector<double> topleft = shape->getTopLeft();
	leftFactor = (newLeft - shape->GetShape()->Width / 2) - topleft[0];
	topFactor = (newTop - shape->GetShape()->Height / 2) - topleft[1];
}

MoveGroupCommand::~MoveGroupCommand()
{
}

//execute that makes a visitor which will visit all of the given shapes children and move them with the move factors
void MoveGroupCommand::Execute()
{
	MoveGroupVisitor moveGroupVisitor = MoveGroupVisitor(canvas, leftFactor, topFactor);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(moveGroupVisitor);
	else if (ellipShape) ellipShape->Accept(moveGroupVisitor);
}

//undo that makes a visitor which will visit all of the given shapes children and move them back with the move factors
void MoveGroupCommand::Undo()
{
	MoveGroupBackVisitor moveGroupBackVisitor = MoveGroupBackVisitor(canvas, leftFactor, topFactor);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(moveGroupBackVisitor);
	else if (ellipShape) ellipShape->Accept(moveGroupBackVisitor);
}

#include "MoveCommand.h"
#include "Rectangle.h"
#include "Ellipse.h"

//constructor which saves the old topleft from the shape and calculates the left and topfactors
MoveCommand::MoveCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop) : canvas(canvas), shape(shape), newLeft(newLeft), newTop(newTop)
{
	std::vector<double> topleft = shape->getTopLeft();
	oldLeft = topleft[0];
	oldTop = topleft[1];
	leftFactor = (newLeft - shape->GetShape()->Width/2) - topleft[0]; //takes pointer center into account
	topFactor =  (newTop - shape->GetShape()->Height/2) - topleft[1]; //takes pointer center into account
}

MoveCommand::~MoveCommand()
{
}

//execute that sets the new topleft using the old topleft and the left and right factor
void MoveCommand::Execute()
{
	shape->setTopLeft(oldLeft + leftFactor, oldTop + topFactor);

	canvas->SetLeft(shape->GetShape(), oldLeft + leftFactor);
	canvas->SetTop(shape->GetShape(), oldTop + topFactor);
}

//undo that sets the topleft back to original position
void MoveCommand::Undo()
{
	shape->setTopLeft(oldLeft, oldTop);

	canvas->SetLeft(shape->GetShape(), oldLeft);
	canvas->SetTop(shape->GetShape(), oldTop);
}

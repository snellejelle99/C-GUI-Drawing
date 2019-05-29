#include "MoveGroupVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

MoveGroupVisitor::MoveGroupVisitor(Windows::UI::Xaml::Controls::Canvas ^canvas, double leftFactor, double topFactor) : canvas(canvas), leftFactor(leftFactor), topFactor(topFactor)
{
}

MoveGroupVisitor::~MoveGroupVisitor()
{
}

//implementation of MoveGroupVisitor for Rectangle
void MoveGroupVisitor::Visit(Rectangle* shape)
{
	std::vector<double> topleft = shape->getTopLeft();
	shape->setTopLeft(topleft[0] + leftFactor, topleft[1] + topFactor);

	canvas->SetLeft(shape->GetShape(), topleft[0] + leftFactor);
	canvas->SetTop(shape->GetShape(), topleft[1] + topFactor);
}

//implementation of ChangeGroupColorVisitor for Ellipse
void MoveGroupVisitor::Visit(Ellipse* shape)
{
	std::vector<double> topleft = shape->getTopLeft();
	shape->setTopLeft(topleft[0] + leftFactor, topleft[1] + topFactor);

	canvas->SetLeft(shape->GetShape(), topleft[0] + leftFactor);
	canvas->SetTop(shape->GetShape(), topleft[1] + topFactor);
}


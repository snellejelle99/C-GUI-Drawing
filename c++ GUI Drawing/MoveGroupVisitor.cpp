#include "MoveGroupVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

MoveGroupVisitor::MoveGroupVisitor(Windows::UI::Xaml::Controls::Canvas ^canvas, double leftFactor, double topFactor) : canvas(canvas), leftFactor(leftFactor), topFactor(topFactor)
{
}

MoveGroupVisitor::~MoveGroupVisitor()
{
}

//visit which shifts the topleft with the given factors
void MoveGroupVisitor::Visit(Rectangle* shape)
{
	std::vector<double> topleft = shape->getTopLeft();
	shape->setTopLeft(topleft[0] + leftFactor, topleft[1] + topFactor);

	canvas->SetLeft(shape->GetShape(), topleft[0] + leftFactor);
	canvas->SetTop(shape->GetShape(), topleft[1] + topFactor);
}

//visit which shifts the topleft with the given factors
void MoveGroupVisitor::Visit(Ellipse* shape)
{
	std::vector<double> topleft = shape->getTopLeft();
	shape->setTopLeft(topleft[0] + leftFactor, topleft[1] + topFactor);

	canvas->SetLeft(shape->GetShape(), topleft[0] + leftFactor);
	canvas->SetTop(shape->GetShape(), topleft[1] + topFactor);
}


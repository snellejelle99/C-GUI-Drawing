#include "ShapeDeleteVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ShapeDeleteVisitor::ShapeDeleteVisitor(Windows::UI::Xaml::Controls::Canvas^ canvas) : canvas(canvas)
{
}

ShapeDeleteVisitor::~ShapeDeleteVisitor()
{
}

void ShapeDeleteVisitor::Visit(Rectangle* shape)
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	canvas->Children->RemoveAt(index);
}

void ShapeDeleteVisitor::Visit(Ellipse* shape)
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	canvas->Children->RemoveAt(index);
}


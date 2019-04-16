#include "ShapeDeleteVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ShapeDeleteVisitor::ShapeDeleteVisitor(Windows::UI::Xaml::Controls::Canvas^ canvas) : canvas(canvas)
{
}

ShapeDeleteVisitor::~ShapeDeleteVisitor()
{
}

//implementation of ShapeDeleteVisitor for Rectangle
void ShapeDeleteVisitor::Visit(Rectangle* shape)
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	canvas->Children->RemoveAt(index);
}

//implementation of ShapeDeleteVisitor for Ellipse
void ShapeDeleteVisitor::Visit(Ellipse* shape)
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	canvas->Children->RemoveAt(index);
}


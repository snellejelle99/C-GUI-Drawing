#include "ShapeAddVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ShapeAddVisitor::ShapeAddVisitor(Windows::UI::Xaml::Controls::Canvas ^ canvas) : canvas(canvas)
{
}

ShapeAddVisitor::~ShapeAddVisitor()
{
}

//implementation of ShapeAddVisitor for Rectangle
void ShapeAddVisitor::Visit(Rectangle * shape)
{
	canvas->Children->Append(shape->GetShape());
}

//implementation of ShapeAddVisitor for Rectangle
void ShapeAddVisitor::Visit(Ellipse * shape)
{
	canvas->Children->Append(shape->GetShape());
}

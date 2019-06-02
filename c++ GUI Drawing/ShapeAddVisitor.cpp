#include "ShapeAddVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ShapeAddVisitor::ShapeAddVisitor(Windows::UI::Xaml::Controls::Canvas ^ canvas) : canvas(canvas)
{
}

ShapeAddVisitor::~ShapeAddVisitor()
{
}

//visit which appends the shape to the canvas
void ShapeAddVisitor::Visit(Rectangle * shape)
{
	canvas->Children->Append(shape->GetShape());
}

//visit which appends the shape to the canvas
void ShapeAddVisitor::Visit(Ellipse * shape)
{
	canvas->Children->Append(shape->GetShape());
}

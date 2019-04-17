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
	if (index < std::numeric_limits<unsigned int>::max())
	{
		canvas->Children->RemoveAt(index);
	}
	shape->DellFromParent();
}

//implementation of ShapeDeleteVisitor for Ellipse
void ShapeDeleteVisitor::Visit(Ellipse* shape)
{
	unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	if (index < std::numeric_limits<unsigned int>::max())
	{
		canvas->Children->RemoveAt(index);
	}
	shape->DellFromParent();
}


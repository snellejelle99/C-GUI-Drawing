#include "ShapeDeleteVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ShapeDeleteVisitor::ShapeDeleteVisitor(Windows::UI::Xaml::Controls::Canvas^ canvas) : canvas(canvas)
{
}

ShapeDeleteVisitor::~ShapeDeleteVisitor()
{
}

//visit which deletes element from the canvas and from its parent
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

//visit which deletes element from the canvas and from its parent
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


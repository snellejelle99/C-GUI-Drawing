#include "Rectangle.h"
#include "Ellipse.h"

Rectangle::Rectangle(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Rectangle ^rect) : Shape(left, top, color), rect(rect)
{

}

Rectangle::~Rectangle()
{
}

void Rectangle::ChangeColor(Windows::UI::Color newColor)
{
	rect->Fill = ref new SolidColorBrush(newColor);
}

bool Rectangle::CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape)
{
	if (shape == this->rect) return true;
	else return false;
}

Windows::UI::Xaml::Shapes::Shape^ Rectangle::GetShape()
{
	return rect;
}

void Rectangle::Accept(ShapeDeleteVisitor shapeDeleteVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.
		
		if (rectShape) rectShape->Accept(shapeDeleteVisitor);
		else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
	}
	shapeDeleteVisitor.Visit(this);
}

void Rectangle::Accept(ShapeAddVisitor shapeAddVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(shapeAddVisitor);
		else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
	}
	shapeAddVisitor.Visit(this);
}

Platform::String^ Rectangle::ToString()
{
	Platform::String^ string = "";
	string += "rect "
		+ left + " " + top + " "
		+ rect->Width + " " + rect->Height + " "
		+ color.A + " " + color.R + " " + color.G + " " + color.B;

	for (Shape* sh : subShapes) {
		string += "\n	" + sh->ToString();
	}

	return string;
}

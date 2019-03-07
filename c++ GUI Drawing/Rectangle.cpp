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
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		
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
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.

		if (rectShape) rectShape->Accept(shapeAddVisitor);
		else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
	}
	shapeAddVisitor.Visit(this);
}

std::string Rectangle::ToString()
{
	std::string string = "";
	string += "rect "
		+ std::to_string(left) + " " + std::to_string(top) + " "
		+ std::to_string(rect->Width) + " " + std::to_string(rect->Height) + " "
		+ std::to_string(color.A) + std::to_string(color.R) + std::to_string(color.G) + std::to_string(color.B);

	return string;
}

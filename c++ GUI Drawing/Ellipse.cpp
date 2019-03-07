#include "Ellipse.h"
#include "Rectangle.h"

Ellipse::Ellipse(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Ellipse ^ellipse) : Shape(left,top, color), ellipse(ellipse)
{

}

Ellipse::~Ellipse()
{
}

void Ellipse::ChangeColor(Windows::UI::Color newColor)
{
	ellipse->Fill = ref new SolidColorBrush(newColor);
}

bool Ellipse::CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape)
{
	if (shape == this->ellipse) return true;
	else return false;
}

Windows::UI::Xaml::Shapes::Shape^ Ellipse::GetShape()
{
	return ellipse;
}

void Ellipse::Accept(ShapeDeleteVisitor shapeDeleteVisitor)
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

void Ellipse::Accept(ShapeAddVisitor shapeAddVisitor)
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

std::string Ellipse::ToString()
{
	std::string string = "";
	string += "ellip "
		+ std::to_string(left) + " " + std::to_string(top) + " "
		+ std::to_string(ellipse->Width) + " " + std::to_string(ellipse->Height) + " "
		+ std::to_string(color.A) + std::to_string(color.R) + std::to_string(color.G) + std::to_string(color.B);

	return string;
}

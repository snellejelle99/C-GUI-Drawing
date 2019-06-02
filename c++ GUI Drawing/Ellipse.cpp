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
	color = newColor;
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
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(shapeDeleteVisitor);
		else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
		i--; //subshape deleted, correction for index shift.
	}
	shapeDeleteVisitor.Visit(this);
}

void Ellipse::Accept(ShapeAddVisitor shapeAddVisitor)
{
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(shapeAddVisitor);
		else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
	}
	shapeAddVisitor.Visit(this);
}

void Ellipse::Accept(ChangeGroupColorVisitor changeGroupColorVisitor)
{
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(changeGroupColorVisitor);
		else if (ellipShape) ellipShape->Accept(changeGroupColorVisitor);
	}
	changeGroupColorVisitor.Visit(this);
}

void Ellipse::Accept(ChangeGroupColorBackVisitor changeGroupColorBackVisitor)
{
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(changeGroupColorBackVisitor);
		else if (ellipShape) ellipShape->Accept(changeGroupColorBackVisitor);
	}
	changeGroupColorBackVisitor.Visit(this);
}

void Ellipse::Accept(MoveGroupVisitor moveGroupVisitor)
{
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(moveGroupVisitor);
		else if (ellipShape) ellipShape->Accept(moveGroupVisitor);
	}
	moveGroupVisitor.Visit(this);
}

void Ellipse::Accept(MoveGroupBackVisitor MoveGroupBackVisitor)
{
	for (unsigned int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(MoveGroupBackVisitor);
		else if (ellipShape) ellipShape->Accept(MoveGroupBackVisitor);
	}
	MoveGroupBackVisitor.Visit(this);
}

Platform::String^ Ellipse::ToString(int counter)
{
	counter++;
	Platform::String^ string = "";
	string += "ellip "
		+ left + " " + top + " "
		+ ellipse->Width + " " + ellipse->Height + " "
		+ color.A + " " + color.R + " " + color.G + " " + color.B;

	for (Shape* sh : subShapes) {
		string += "\n";
		for (int i = 0; i < counter; i++) {
			string += " ";
		}		
		string += sh->ToString(counter);
	}

	return string;
}

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
	color = newColor;
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

//implementation of shapeAccept for deleteVisitor
void Rectangle::Accept(ShapeDeleteVisitor shapeDeleteVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.
		
		if (rectShape) rectShape->Accept(shapeDeleteVisitor);
		else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
		i--; //subshape deleted, correction for index shift.
	}
	shapeDeleteVisitor.Visit(this);
}

//implementation of shapeAccept for addVisitor
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

void Rectangle::Accept(ChangeGroupColorVisitor changeGroupColorVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(changeGroupColorVisitor);
		else if (ellipShape) ellipShape->Accept(changeGroupColorVisitor);
	}
	changeGroupColorVisitor.Visit(this);
}

void Rectangle::Accept(ChangeGroupColorBackVisitor changeGroupColorBackVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(changeGroupColorBackVisitor);
		else if (ellipShape) ellipShape->Accept(changeGroupColorBackVisitor);
	}
	changeGroupColorBackVisitor.Visit(this);
}

void Rectangle::Accept(MoveGroupVisitor moveGroupVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(moveGroupVisitor);
		else if (ellipShape) ellipShape->Accept(moveGroupVisitor);
	}
	moveGroupVisitor.Visit(this);
}

void Rectangle::Accept(MoveGroupBackVisitor MoveGroupBackVisitor)
{
	for (int i = 0; i < subShapes.size(); i++)
	{
		Rectangle* rectShape = dynamic_cast<Rectangle*>(subShapes[i]); // Will return nullptr if rectShape isn't a Rectangle.
		Ellipse* ellipShape = dynamic_cast<Ellipse*>(subShapes[i]); // Will return nullptr if ellipShape isn't a Elipse.

		if (rectShape) rectShape->Accept(MoveGroupBackVisitor);
		else if (ellipShape) ellipShape->Accept(MoveGroupBackVisitor);
	}
	MoveGroupBackVisitor.Visit(this);
}


Platform::String^ Rectangle::ToString(int counter)
{
	counter++;
	Platform::String^ string = "";
	string += "rect "
		+ left + " " + top + " "
		+ rect->Width + " " + rect->Height + " "
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

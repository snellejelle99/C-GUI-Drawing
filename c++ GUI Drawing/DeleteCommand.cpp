#include "DeleteCommand.h"
#include "ShapeDeleteVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <algorithm>

DeleteCommand::DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, std::vector<Shape*> &shapes) : canvas(canvas), shape(shape), shapes(shapes)
{
}

DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::Execute()
{
	savedSubShapes = shape->GetSubShapes();
	shapes.erase(remove(shapes.begin(), shapes.end(), shape), shapes.end());

	ShapeDeleteVisitor shapeDeleteVisitor = ShapeDeleteVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeDeleteVisitor);
	else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
}

void DeleteCommand::Undo()
{
	for (Shape* ps : shape->GetParentShapes()) ps->AddSubShape(shape);

	for (Shape* subShape : savedSubShapes) 
	{
		for(Shape* parent : subShape->GetParentShapes())
		{
			parent->AddSubShape(subShape);
		}
	}

	shapes.push_back(shape);
	ShapeAddVisitor shapeAddVisitor = ShapeAddVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeAddVisitor);
	else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
}

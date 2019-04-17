#include "DeleteCommand.h"
#include "ShapeDeleteVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

DeleteCommand::DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape) : canvas(canvas), shape(shape)
{
}

DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::Execute()
{
	savedSubShapes = shape->GetSubShapes();
	//std::copy(subShapes.begin(), subShapes.end(), std::back_inserter(savedSubShapes));
	ShapeDeleteVisitor shapeDeleteVisitor = ShapeDeleteVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeDeleteVisitor);
	else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);
}

void DeleteCommand::Undo()
{
	//for (Shape* ss : savedSubShapes) shape->AddSubShape(ss);
	for (Shape* ps : shape->GetParentShapes()) ps->AddSubShape(shape);

	for (Shape* subShape : savedSubShapes) 
	{
		for(Shape* parent : subShape->GetParentShapes())
		{
			parent->AddSubShape(subShape);
		}
	}

	ShapeAddVisitor shapeAddVisitor = ShapeAddVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeAddVisitor);
	else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
}

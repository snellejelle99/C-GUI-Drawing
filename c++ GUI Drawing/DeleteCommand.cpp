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
	ShapeDeleteVisitor shapeDeleteVisitor = ShapeDeleteVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeDeleteVisitor);
	else if (ellipShape) ellipShape->Accept(shapeDeleteVisitor);

	/*unsigned int index = 0;
	canvas->Children->IndexOf(shape->GetShape(), &index);
	canvas->Children->RemoveAt(index);*/
}

void DeleteCommand::Undo()
{
	ShapeAddVisitor shapeAddVisitor = ShapeAddVisitor(canvas);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(shapeAddVisitor);
	else if (ellipShape) ellipShape->Accept(shapeAddVisitor);
	//canvas->Children->Append(shape->GetShape());
}

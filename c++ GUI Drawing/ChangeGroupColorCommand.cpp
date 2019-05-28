#include "ChangeGroupColorCommand.h"
#include "ChangeGroupColorVisitor.h"
#include "ChangeGroupColorBackVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <tuple>

ChangeGroupColorCommand::ChangeGroupColorCommand(Shape* shape, Windows::UI::Color newColor) : shape(shape), newColor(newColor)
{
	std::tuple<Shape*, Windows::UI::Color> oldcolortuple;
	std::vector<Shape*> subshapes = shape->GetSubShapes();

	oldcolortuple = std::make_tuple(shape, shape->GetColor());
	oldColors.push_back(oldcolortuple);

	for (Shape* sh : subshapes)
	{
		oldcolortuple = std::make_tuple(sh, sh->GetColor());
		oldColors.push_back(oldcolortuple);
	}
}

ChangeGroupColorCommand::~ChangeGroupColorCommand()
{
}

void ChangeGroupColorCommand::Execute()
{
	ChangeGroupColorVisitor changeGroupColorVisitor = ChangeGroupColorVisitor(newColor);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(changeGroupColorVisitor);
	else if (ellipShape) ellipShape->Accept(changeGroupColorVisitor);
}

void ChangeGroupColorCommand::Undo()
{
	ChangeGroupColorBackVisitor changeGroupColorBackVisitor = ChangeGroupColorBackVisitor(oldColors);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(changeGroupColorBackVisitor);
	else if (ellipShape) ellipShape->Accept(changeGroupColorBackVisitor);
}
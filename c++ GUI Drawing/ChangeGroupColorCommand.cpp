#include "ChangeGroupColorCommand.h"
#include "ChangeGroupColorVisitor.h"
#include "ChangeGroupColorBackVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <tuple>

//constructor that gets all the children of the given shape and saves their color in a tuple vector.
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

//execute that creates a visitor wich visits all the children of the given shape and changes the color to the new color
void ChangeGroupColorCommand::Execute()
{
	ChangeGroupColorVisitor changeGroupColorVisitor = ChangeGroupColorVisitor(newColor);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(changeGroupColorVisitor);
	else if (ellipShape) ellipShape->Accept(changeGroupColorVisitor);
}

//undo that creates a visitor wich wisits all the children and changes the color back to its original color with the saved tuple vector.
void ChangeGroupColorCommand::Undo()
{
	ChangeGroupColorBackVisitor changeGroupColorBackVisitor = ChangeGroupColorBackVisitor(oldColors);
	Rectangle* rectShape = dynamic_cast<Rectangle*>(shape); // Will return nullptr if rectShape isn't a Rectangle.
	Ellipse* ellipShape = dynamic_cast<Ellipse*>(shape); // Will return nullptr if rectShape isn't a Rectangle.

	if (rectShape) rectShape->Accept(changeGroupColorBackVisitor);
	else if (ellipShape) ellipShape->Accept(changeGroupColorBackVisitor);
}
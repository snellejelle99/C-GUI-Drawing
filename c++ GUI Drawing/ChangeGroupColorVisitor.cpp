#include "ChangeGroupColorVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ChangeGroupColorVisitor::ChangeGroupColorVisitor(Windows::UI::Color newColor) : newColor(newColor)
{
}

ChangeGroupColorVisitor::~ChangeGroupColorVisitor()
{
}

//visit which changes the color of the given shape
void ChangeGroupColorVisitor::Visit(Rectangle* shape)
{
	shape->ChangeColor(newColor);
}

//visit which changes the color of the given shape
void ChangeGroupColorVisitor::Visit(Ellipse* shape)
{
	shape->ChangeColor(newColor);
}


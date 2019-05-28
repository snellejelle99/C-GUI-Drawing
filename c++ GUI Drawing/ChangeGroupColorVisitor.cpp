#include "ChangeGroupColorVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ChangeGroupColorVisitor::ChangeGroupColorVisitor(Windows::UI::Color newColor) : newColor(newColor)
{
}

ChangeGroupColorVisitor::~ChangeGroupColorVisitor()
{
}

//implementation of ChangeGroupColorVisitor for Rectangle
void ChangeGroupColorVisitor::Visit(Rectangle* shape)
{
	shape->ChangeColor(newColor);
}

//implementation of ChangeGroupColorVisitor for Ellipse
void ChangeGroupColorVisitor::Visit(Ellipse* shape)
{
	shape->ChangeColor(newColor);
}


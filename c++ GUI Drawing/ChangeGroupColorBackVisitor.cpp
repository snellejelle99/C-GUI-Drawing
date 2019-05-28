#include "ChangeGroupColorBackVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ChangeGroupColorBackVisitor::ChangeGroupColorBackVisitor(std::vector<std::tuple<Shape*, Windows::UI::Color>> &oldColors) : oldColors(oldColors)
{
}

ChangeGroupColorBackVisitor::~ChangeGroupColorBackVisitor()
{
}

//implementation of ChangeGroupColorVisitor for Rectangle
void ChangeGroupColorBackVisitor::Visit(Rectangle* shape)
{
	for (std::tuple<Shape*, Windows::UI::Color> octuple : oldColors)
	{
		if (shape == std::get<Shape*>(octuple))
		{
			shape->ChangeColor(std::get<Windows::UI::Color>(octuple));
		}
	}
}

//implementation of ChangeGroupColorVisitor for Ellipse
void ChangeGroupColorBackVisitor::Visit(Ellipse* shape)
{
	for (std::tuple<Shape*, Windows::UI::Color> octuple : oldColors)
	{
		if (shape == std::get<Shape*>(octuple))
		{
			shape->ChangeColor(std::get<Windows::UI::Color>(octuple));
		}
	}
}


#include "ChangeGroupColorBackVisitor.h"
#include "Rectangle.h"
#include "Ellipse.h"

ChangeGroupColorBackVisitor::ChangeGroupColorBackVisitor(std::vector<std::tuple<Shape*, Windows::UI::Color>> &oldColors) : oldColors(oldColors)
{
}

ChangeGroupColorBackVisitor::~ChangeGroupColorBackVisitor()
{
}

//visit which loops trough the oldcolor vector and gives the shape its old color
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

//visit which loops trough the oldcolor vector and gives the shape its old color
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


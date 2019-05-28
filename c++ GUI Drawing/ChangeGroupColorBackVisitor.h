#ifndef CHANGEGROUPCOLORBACKVISITOR
#define CHANGEGROUPCOLORBACKVISITOR

#include "ShapeVisitor.h"
#include <vector>
#include <tuple>
#include "Shape.h"

//ChangeGroupColorVisitorBack class defenition
class ChangeGroupColorBackVisitor : public ShapeVisitor
{
public:
	ChangeGroupColorBackVisitor(std::vector<std::tuple<Shape*, Windows::UI::Color>> &oldColors);
	~ChangeGroupColorBackVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	std::vector<std::tuple<Shape*, Windows::UI::Color>> &oldColors;
};

#endif // ! CHANGEGROUPCOLORVISITORBACK

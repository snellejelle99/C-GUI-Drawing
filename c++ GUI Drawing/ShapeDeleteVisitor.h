#ifndef SHAPEDELVISITOR
#define SHAPEDELVISITOR

#include "ShapeVisitor.h"

//ShapeDeleteVisitor class defenition
class ShapeDeleteVisitor : public ShapeVisitor
{
public:
	ShapeDeleteVisitor(Windows::UI::Xaml::Controls::Canvas^ canvas);
	~ShapeDeleteVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	Windows::UI::Xaml::Controls::Canvas ^canvas;
};

#endif // !SHAPEDELVISITOR

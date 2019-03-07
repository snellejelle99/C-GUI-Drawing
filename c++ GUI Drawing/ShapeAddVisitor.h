#ifndef SHAPEADDVISITOR
#define SHAPEADDVISITOR

#include "ShapeVisitor.h"

class ShapeAddVisitor : public ShapeVisitor
{
public:
	ShapeAddVisitor(Windows::UI::Xaml::Controls::Canvas^ canvas);
	~ShapeAddVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	Windows::UI::Xaml::Controls::Canvas ^canvas;
};

#endif
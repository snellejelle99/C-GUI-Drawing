#ifndef SHAPEVISITOR
#define SHAPEVISITOR

//#include "Rectangle.h"
//#include "Ellipse.h"
class Rectangle;
class Ellipse;

class ShapeVisitor
{
public:
	virtual void Visit(Rectangle* shape) = 0;
	virtual void Visit(Ellipse* shape) = 0;
};
#endif // !SHAPEVISITOR



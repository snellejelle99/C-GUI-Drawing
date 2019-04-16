#ifndef SHAPEVISITOR
#define SHAPEVISITOR

class Rectangle;
class Ellipse;

//interface that defines the Visit for Rectangle and Ellipse
class ShapeVisitor
{
public:
	virtual void Visit(Rectangle* shape) = 0;
	virtual void Visit(Ellipse* shape) = 0;
};
#endif // !SHAPEVISITOR



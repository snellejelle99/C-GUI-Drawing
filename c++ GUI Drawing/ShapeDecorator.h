#ifndef SHAPEDECORATOR
#define SHAPEDECORATOR

#include "Shape.h"

//definition of the shapedecorator class with a virtual draw method
class ShapeDecorator
{
public:
	ShapeDecorator(Shape* shape);
	~ShapeDecorator();
	virtual void Draw() = 0;

protected:
	Shape* shape;
};

#endif //!SHAPEDECORATOR
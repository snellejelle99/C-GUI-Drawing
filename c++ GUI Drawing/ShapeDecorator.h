#ifndef SHAPEDECORATOR
#define SHAPEDECORATOR

#include "Shape.h"

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
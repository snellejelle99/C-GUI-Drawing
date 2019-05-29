#ifndef NOBORDERDECORATOR
#define NOBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

class NoBorderDecorator : public ShapeDecorator
{
public:
	NoBorderDecorator(Shape* shape);
	~NoBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
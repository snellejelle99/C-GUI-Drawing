#ifndef NOBORDERDECORATOR
#define NOBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

//border decorator which inherits from ShapeDecorator
class NoBorderDecorator : public ShapeDecorator
{
public:
	NoBorderDecorator(Shape* shape);
	~NoBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
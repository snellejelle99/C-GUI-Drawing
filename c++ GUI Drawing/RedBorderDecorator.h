#ifndef REDBORDERDECORATOR
#define REDBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

class RedBorderDecorator : public ShapeDecorator
{
public:
	RedBorderDecorator(Shape* shape);
	~RedBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
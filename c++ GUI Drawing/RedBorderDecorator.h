#ifndef REDBORDERDECORATOR
#define REDBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

//border decorator which inherits from ShapeDecorator
class RedBorderDecorator : public ShapeDecorator
{
public:
	RedBorderDecorator(Shape* shape);
	~RedBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
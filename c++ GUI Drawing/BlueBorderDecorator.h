#ifndef BLUEBORDERDECORATOR
#define BLUEBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

class BlueBorderDecorator : public ShapeDecorator
{
public:
	BlueBorderDecorator(Shape* shape);
	~BlueBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
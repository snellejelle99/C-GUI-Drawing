#ifndef BLUEBORDERDECORATOR
#define BLUEBORDERDECORATOR

#include "Shape.h"
#include "ShapeDecorator.h"

//border decorator which inherits from ShapeDecorator
class BlueBorderDecorator : public ShapeDecorator
{
public:
	BlueBorderDecorator(Shape* shape);
	~BlueBorderDecorator();
	virtual void Draw();
};

#endif //!SHAPEDECORATOR
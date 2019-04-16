#ifndef SHAPEACCEPT
#define SHAPEACCEPT

#include "ShapeDeleteVisitor.h"
#include "ShapeAddVisitor.h"

//interface that defines the Accept for shapeDeleteVisitor and ShapeAddVisitor
class ShapeAccept
{
public:
	virtual void Accept(ShapeDeleteVisitor shapeDeleteVisitor) = 0;
	virtual void Accept(ShapeAddVisitor shapeAddVisistor) = 0;
};
#endif // !SHAPEDELACCEPT

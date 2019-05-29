#ifndef SHAPEACCEPT
#define SHAPEACCEPT

#include "ShapeDeleteVisitor.h"
#include "ShapeAddVisitor.h"
#include "ChangeGroupColorVisitor.h"
#include "ChangeGroupColorBackVisitor.h"
#include "MoveGroupVisitor.h"
#include "MoveGroupBackVisitor.h"

//interface that defines the Accept for shapeDeleteVisitor and ShapeAddVisitor
class ShapeAccept
{
public:
	virtual void Accept(ShapeDeleteVisitor shapeDeleteVisitor) = 0;
	virtual void Accept(ShapeAddVisitor shapeAddVisistor) = 0;
	virtual void Accept(ChangeGroupColorVisitor changeGroupColorVisitor) = 0;
	virtual void Accept(ChangeGroupColorBackVisitor changeGroupColorBackVisitor) = 0;
	virtual void Accept(MoveGroupVisitor moveGroupVisitor) = 0;
	virtual void Accept(MoveGroupBackVisitor moveGroupBackVisitor) = 0;
};
#endif // !SHAPEDELACCEPT

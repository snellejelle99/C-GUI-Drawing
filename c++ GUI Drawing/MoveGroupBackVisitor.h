#ifndef MOVEGROUPBACKVISITOR
#define MOVEGROUPBACKVISITOR

#include "ShapeVisitor.h"

//MoveGroupVisitor class defenition
class MoveGroupBackVisitor : public ShapeVisitor
{
public:
	MoveGroupBackVisitor(Windows::UI::Xaml::Controls::Canvas ^canvas, double leftfactor, double topfactor);
	~MoveGroupBackVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	double leftFactor, topFactor;
};

#endif // ! MOVEGROUPBACKVISITOR

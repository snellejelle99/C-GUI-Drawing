#ifndef MOVEGROUPVISITOR
#define MOVEGROUPVISITOR

#include "ShapeVisitor.h"

//MoveGroupVisitor class defenition
class MoveGroupVisitor : public ShapeVisitor
{
public:
	MoveGroupVisitor(Windows::UI::Xaml::Controls::Canvas ^canvas, double leftfactor, double topfactor);
	~MoveGroupVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	double leftFactor, topFactor;
};

#endif // ! MOVEGROUPVISITOR

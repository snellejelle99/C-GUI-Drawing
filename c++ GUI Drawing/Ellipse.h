#ifndef ELLIPSE
#define ELLIPSE

#include "Shape.h"
#include "ShapeAccept.h"

class Ellipse : public Shape, public ShapeAccept
{
public:
	Ellipse(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Ellipse ^ellipse);
	~Ellipse();

	virtual void ChangeColor(Windows::UI::Color newColor);
	virtual bool CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape);
	virtual Windows::UI::Xaml::Shapes::Shape^ GetShape();
	virtual void Accept(ShapeDeleteVisitor shapeDeleteVisitor);
	virtual void Accept(ShapeAddVisitor shapeAddVisitor);
	virtual void Accept(ChangeGroupColorVisitor changeGroupColorVisitor);
	virtual void Accept(ChangeGroupColorBackVisitor changeGroupColorBackVisitor);
	virtual void Accept(MoveGroupVisitor moveGroupVisitor);
	virtual void Accept(MoveGroupBackVisitor moveGroupBackVisitor);
	virtual Platform::String^ ToString(int counter = 0);

private:
	Windows::UI::Xaml::Shapes::Ellipse ^ellipse;
};



#endif
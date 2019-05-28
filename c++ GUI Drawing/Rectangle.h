#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"
#include "ShapeAccept.h"

class Rectangle : public Shape, public ShapeAccept
{
public:
	Rectangle(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Rectangle ^rect );
	~Rectangle();

	virtual void ChangeColor(Windows::UI::Color newColor);
	virtual bool CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape);
	virtual Windows::UI::Xaml::Shapes::Shape^ GetShape();
	virtual void Accept(ShapeDeleteVisitor shapeDeleteVisitor);
	virtual void Accept(ShapeAddVisitor shapeAddVisitor);
	virtual Platform::String^ ToString(int counter = 0);

private:
	Windows::UI::Xaml::Shapes::Rectangle ^rect;
};


#endif // !Rectangle
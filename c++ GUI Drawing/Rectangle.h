#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"



class Rectangle : public Shape
{
public:
	Rectangle(double left, double top, Windows::UI::Xaml::Shapes::Rectangle ^rect );
	~Rectangle();

private:
	Windows::UI::Xaml::Shapes::Rectangle ^rect;

};


#endif // !Rectangle
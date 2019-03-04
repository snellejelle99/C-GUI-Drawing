#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"



class Rectangle : public Shape
{
public:
	Rectangle(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Rectangle ^rect );
	~Rectangle();

	virtual void ChangeColor(Windows::UI::Color newColor);

	virtual std::string ToString();

private:
	Windows::UI::Xaml::Shapes::Rectangle ^rect;

};


#endif // !Rectangle
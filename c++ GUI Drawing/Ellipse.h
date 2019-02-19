#ifndef ELLIPSE
#define ELLISPE

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(double left, double top, Windows::UI::Xaml::Shapes::Ellipse ^ellipse);
	~Ellipse();

private:
	Windows::UI::Xaml::Shapes::Ellipse ^ellipse;

};



#endif
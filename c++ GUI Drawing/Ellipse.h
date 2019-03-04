#ifndef ELLIPSE
#define ELLISPE

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Ellipse ^ellipse);
	~Ellipse();

	virtual void ChangeColor(Windows::UI::Color newColor);
	virtual std::string ToString();

private:
	Windows::UI::Xaml::Shapes::Ellipse ^ellipse;

};



#endif
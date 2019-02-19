#include "Ellipse.h"


Ellipse::Ellipse(double left, double top, Windows::UI::Xaml::Shapes::Ellipse ^ellipse) : Shape(left,top), ellipse(ellipse)
{

}

Ellipse::~Ellipse()
{
}
#include "Ellipse.h"


Ellipse::Ellipse(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Ellipse ^ellipse) : Shape(left,top, color), ellipse(ellipse)
{

}

Ellipse::~Ellipse()
{
}

void Ellipse::ChangeColor(Windows::UI::Color newColor)
{
	ellipse->Fill = ref new SolidColorBrush(newColor);
}

bool Ellipse::CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape)
{
	if (shape == this->ellipse) return true;
	else return false;
}
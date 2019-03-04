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

std::string Ellipse::ToString()
{
	std::string string = "";
	string += "ellip "
		+ std::to_string(left) + " " + std::to_string(top) + " "
		+ std::to_string(ellipse->Width) + " " + std::to_string(ellipse->Height) + " "
		+ std::to_string(color.A) + std::to_string(color.R) + std::to_string(color.G) + std::to_string(color.B);

	return string;
}

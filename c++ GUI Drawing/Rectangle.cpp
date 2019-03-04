#include "Rectangle.h"


Rectangle::Rectangle(double left, double top, Windows::UI::Color color, Windows::UI::Xaml::Shapes::Rectangle ^rect) : Shape(left, top, color), rect(rect)
{

}

Rectangle::~Rectangle()
{
}

void Rectangle::ChangeColor(Windows::UI::Color newColor)
{
	rect->Fill = ref new SolidColorBrush(newColor);
}

bool Rectangle::CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape)
{
	if (shape == this->rect) return true;
	else return false;
}

std::string Rectangle::ToString()
{
	std::string string = "";
	string += "rect "
		+ std::to_string(left) + " " + std::to_string(top) + " "
		+ std::to_string(rect->Width) + " " + std::to_string(rect->Height) + " "
		+ std::to_string(color.A) + std::to_string(color.R) + std::to_string(color.G) + std::to_string(color.B);

	return string;
}

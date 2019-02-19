#include "Rectangle.h"


Rectangle::Rectangle(double left, double top, Windows::UI::Xaml::Shapes::Rectangle ^rect) : Shape(left, top), rect(rect)
{

}

Rectangle::~Rectangle()
{
}

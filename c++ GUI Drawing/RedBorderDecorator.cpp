#include "RedBorderDecorator.h"

RedBorderDecorator::RedBorderDecorator(Shape * shape) : ShapeDecorator(shape)
{
}

RedBorderDecorator::~RedBorderDecorator()
{
}

//draw function which draws a red border on a shape
void RedBorderDecorator::Draw()
{
	shape->GetShape()->Stroke = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));
}

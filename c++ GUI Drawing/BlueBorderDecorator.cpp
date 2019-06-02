#include "BlueBorderDecorator.h"

BlueBorderDecorator::BlueBorderDecorator(Shape * shape) : ShapeDecorator(shape)
{
}

BlueBorderDecorator::~BlueBorderDecorator()
{
}

//draw function which draws a blue border on a shape
void BlueBorderDecorator::Draw()
{
	shape->GetShape()->Stroke = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(225, 0, 0, 225));
}

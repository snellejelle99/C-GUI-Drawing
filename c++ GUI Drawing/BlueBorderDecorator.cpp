#include "BlueBorderDecorator.h"

BlueBorderDecorator::BlueBorderDecorator(Shape * shape) : ShapeDecorator(shape)
{
}

BlueBorderDecorator::~BlueBorderDecorator()
{
}

void BlueBorderDecorator::Draw()
{
	shape->GetShape()->Stroke = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(225, 0, 0, 225));
}

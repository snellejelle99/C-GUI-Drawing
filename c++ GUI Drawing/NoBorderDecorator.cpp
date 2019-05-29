#include "NoBorderDecorator.h"

NoBorderDecorator::NoBorderDecorator(Shape * shape) : ShapeDecorator(shape)
{
}

NoBorderDecorator::~NoBorderDecorator()
{
}

void NoBorderDecorator::Draw()
{
	shape->GetShape()->Stroke = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0, 0, 0, 0));
}

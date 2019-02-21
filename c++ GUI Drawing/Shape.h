#ifndef SHAPE
#define SHAPE

using namespace Windows::UI::Xaml::Media;

class Shape
{
public:
	Shape(double left, double top, Windows::UI::Color color);
	~Shape();

	Windows::UI::Color GetColor();

	virtual void ChangeColor(Windows::UI::Color newColor) = 0;

protected:
	double left;
	double top;
	Windows::UI::Color color;

};


#endif
#ifndef SHAPE
#define SHAPE

class Shape
{
public:
	Shape(double left, double top, Windows::UI::Color color);
	~Shape();

protected:
	double left;
	double top;
	Windows::UI::Color color;

};


#endif
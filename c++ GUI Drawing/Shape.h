#ifndef SHAPE
#define SHAPE

#include <string>
#include <vector>

using namespace Windows::UI::Xaml::Media;

class Shape
{
public:
	Shape(double left, double top, Windows::UI::Color color);
	~Shape();

	Windows::UI::Color GetColor();
	void AddSubShape(Shape* subShape);
	void DelSubShape(Shape* subShape);

	virtual void ChangeColor(Windows::UI::Color newColor) = 0;
	virtual bool CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape) = 0;
	virtual Windows::UI::Xaml::Shapes::Shape^ GetShape() = 0;
	virtual std::string ToString() = 0;

protected:
	double left;
	double top;
	Windows::UI::Color color;
	std::vector<Shape*> subShapes;
};


#endif
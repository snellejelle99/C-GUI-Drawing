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

	Windows::UI::Color GetColor(); //returns the color of the shape
	void AddSubShape(Shape* subShape);
	void DelSubShape(Shape* subShape);

	virtual void ChangeColor(Windows::UI::Color newColor) = 0; //changes the color of the shape
	virtual bool CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape) = 0;
	virtual Windows::UI::Xaml::Shapes::Shape^ GetShape() = 0;
	virtual Platform::String^ ToString() = 0; //returns a string with parameters of the object

protected:
	double left;
	double top;
	Windows::UI::Color color;
	std::vector<Shape*> subShapes;
};


#endif
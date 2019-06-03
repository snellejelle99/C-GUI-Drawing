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
	bool AddSubShape(Shape* subShape);
	void DelSubShape(Shape* subShape);
	std::vector<double> getTopLeft();
	void setTopLeft(double left, double top);
	const std::vector<Shape*> GetSubShapes(); //return a list containing every shape beneath this shape recursively
	const std::vector<Shape*> GetAllParents(); // return a list containing every shape above this shape recursively

	bool CheckIfParent(Shape* pShape); //check recursivley if this shape is a parent of one of the above shapes
	bool CheckIfSubShape(Shape* shape);  //check recursivley if this shape is a parent of one of the above shapes
	
	void DellFromParent(); //deletes this shape in the subshapes list of the parent
	const std::vector<Shape*> GetParentShapes(); //returns the list of parent shapes


	//STRATEGY PATTERN
	virtual void ChangeColor(Windows::UI::Color newColor) = 0; //changes the color of the shape
	virtual bool CheckShape(Windows::UI::Xaml::Shapes::Shape^ shape) = 0; //check if the windows matches the windows shape in the shape object
	virtual Windows::UI::Xaml::Shapes::Shape^ GetShape() = 0; //returns the
	virtual Platform::String^ ToString(int counter = 0) = 0; //returns a string with parameters of the object

protected:
	double left;
	double top;
	Windows::UI::Color color;
	std::vector<Shape*> parentShapes;
	std::vector<Shape*> subShapes;

	//functions
	bool AddParent(Shape* pShape); //adds a shape to the parent list
};


#endif
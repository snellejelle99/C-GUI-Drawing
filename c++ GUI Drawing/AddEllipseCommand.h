#ifndef ADDELLIPCMD
#define ADDELLIPCMD

#include "Command.h"
#include "Shape.h"
#include <vector>

class AddEllipseCommand : public Command
{
public:
	AddEllipseCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, std::vector<Shape*> &shapes, Windows::UI::Xaml::Shapes::Ellipse ^ellip, Windows::UI::Color color);
	~AddEllipseCommand();

	virtual void Execute();
	virtual void Undo();
private:
	bool isExecuted = false;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	Shape* shape;
	Windows::UI::Xaml::Shapes::Ellipse ^ellip;
	Windows::UI::Color color;
};
#endif
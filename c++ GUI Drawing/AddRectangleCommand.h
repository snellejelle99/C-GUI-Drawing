#ifndef ADDRECTCMD
#define ADDRECTCMD

#include "Command.h"
#include "Rectangle.h"
#include <vector>

class AddRectangleCommand : public Command
{
public:
	AddRectangleCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, std::vector<Shape*> &shapes, Windows::UI::Xaml::Shapes::Rectangle ^rect, Windows::UI::Color color);
	~AddRectangleCommand();

	virtual void Execute();
	virtual void Undo();
private:
	bool isExecuted = false;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	Shape* shape;
	Windows::UI::Xaml::Shapes::Rectangle ^rect;
	Windows::UI::Color color;
};
#endif
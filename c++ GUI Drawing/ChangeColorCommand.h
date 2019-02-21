#pragma once
#include "Command.h"
#include "Shape.h"
class ChangeColorCommand :
	public Command
{
public:
	ChangeColorCommand(Shape & shape, Windows::UI::Color color);
	~ChangeColorCommand();

private:
	Shape shape;
	Windows::UI::Color color;

};


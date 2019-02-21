#ifndef CHANGECOLORCMD
#define CHANGECOLORCMD

#include "Command.h"
#include "Shape.h"

class ChangeColorCommand :
	public Command
{
public:
	ChangeColorCommand(Shape & shape, Windows::UI::Color newColor);
	~ChangeColorCommand();

	virtual void Execute();
	virtual void Undo();

private:
	Shape shape;
	Windows::UI::Color newColor;
	Windows::UI::Color oldColor;

};

#endif
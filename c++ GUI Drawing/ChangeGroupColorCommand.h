#ifndef CHANGEGROUPCOLORCMD
#define CHANGEGROUPCOLORCMD

#include "Command.h"
#include "Shape.h"

class ChangeGroupColorCommand :
	public Command
{
public:
	ChangeGroupColorCommand(Shape* shape, Windows::UI::Color newColor);
	~ChangeGroupColorCommand();

	virtual void Execute();
	virtual void Undo();

private:
	Shape* shape;
	Windows::UI::Color newColor;
	Windows::UI::Color oldColor;

};
#endif // !CHANGEGROUPCOLORCMD

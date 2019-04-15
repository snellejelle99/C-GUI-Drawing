#ifndef GROUPCMD
#define GROUPCMD

#include "Command.h"
#include "Shape.h"

class GroupCommand : public Command
{
public:
	GroupCommand(Shape* shape, Shape* subShape);
	~GroupCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Shape* shape;
	Shape* subShape;
};

#endif 
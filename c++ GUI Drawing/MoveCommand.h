#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"
#include "Shape.h"

class MoveCommand : public Command
{
public:
	MoveCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop);
	~MoveCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Shape* shape;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	double newLeft, newTop, oldLeft, oldTop;
};


#endif // !DELCOMMAND
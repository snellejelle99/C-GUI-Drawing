#ifndef MOVEGROUPCOMMAND
#define MOVEGROUPCOMMAND

#include "Command.h"
#include "Shape.h"

class MoveGroupCommand : public Command
{
public:
	MoveGroupCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, double newLeft, double newTop);
	~MoveGroupCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Shape* shape;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
	double leftFactor, topFactor;
};

#endif // !MOVEGROUPCOMMAND


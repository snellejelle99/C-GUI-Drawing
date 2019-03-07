#ifndef DELCOMMAND
#define DELCOMMAND

#include "Command.h"
#include "Shape.h"

class DeleteCommand : public Command 
{
public:
	DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape);
	~DeleteCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Shape* shape;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
};


#endif // !DELCOMMAND

#ifndef DELCOMMAND
#define DELCOMMAND

#include "Command.h"

class DeleteCommand : public Command 
{
public:
	DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Windows::UI::Xaml::Shapes::Shape^ shape);
	~DeleteCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Windows::UI::Xaml::Shapes::Shape^ shape;
	Windows::UI::Xaml::Controls::Canvas ^canvas;
};


#endif // !DELCOMMAND

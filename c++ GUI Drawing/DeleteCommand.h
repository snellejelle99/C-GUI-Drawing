#ifndef DELCOMMAND
#define DELCOMMAND

#include "Command.h"
#include "Shape.h"

class DeleteCommand : public Command 
{
public:
	DeleteCommand(Windows::UI::Xaml::Controls::Canvas ^canvas, Shape* shape, std::vector<Shape*> &shapes);
	~DeleteCommand();

	virtual void Execute();
	virtual void Undo();
private:
	Shape* shape;
	std::vector<Shape*> savedSubShapes; //subshapes list from shapes before deletecommand is executed (used for undo)
	std::vector<Shape*> &shapes; //refrence to top-layer shape list
	Windows::UI::Xaml::Controls::Canvas ^canvas;
};


#endif // !DELCOMMAND

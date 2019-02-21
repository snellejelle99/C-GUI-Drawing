#ifndef COMMAND
#define COMMAND
class Command
{
public:
	virtual void Execute() = 0;

	virtual void Undo() = 0;
};

#endif
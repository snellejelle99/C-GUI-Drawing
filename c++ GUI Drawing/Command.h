#ifndef COMMAND
#define COMMAND

//virtual classs that defines the execute and undo method of commands
class Command
{
public:
	virtual void Execute() = 0;

	virtual void Undo() = 0;
};

#endif
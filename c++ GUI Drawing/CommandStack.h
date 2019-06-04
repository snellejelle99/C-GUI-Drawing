#ifndef CMDSTACK
#define CMDSTACK
#include "Command.h"
#include <stack>

class CMDStack
{
public:
	CMDStack();
	CMDStack(const std::stack<Command*> executeStack, const std::stack<Command*> revertStack);
	~CMDStack();
	void Add(Command * const newCMD);
	void Undo();
	void Redo();
	void Flush(); //empties the commandstack
private:
	std::stack<Command*> executeStack; // is geexecute
	std::stack<Command*> revertStack; // is gerevert
};
#endif // !

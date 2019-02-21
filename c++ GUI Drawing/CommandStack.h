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
	Command* Undo();
	Command* Redo();
private:
	std::stack<Command*> executeStack;
	std::stack<Command*> revertStack;
};
#endif // !

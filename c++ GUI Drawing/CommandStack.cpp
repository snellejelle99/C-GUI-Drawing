#include "CommandStack.h"

CMDStack::CMDStack()
{
}

CMDStack::CMDStack(const std::stack<Command*> executeStack, const std::stack<Command*> revertStack) : executeStack(executeStack), revertStack(revertStack)
{
}

void CMDStack::Add(Command * const newCMD)
{
	executeStack.push(newCMD);
}

Command* CMDStack::Undo()
{
	revertStack.push(executeStack.top());
	executeStack.pop();
	return revertStack.top();
}

Command* CMDStack::Redo()
{
	executeStack.push(revertStack.top());
	revertStack.pop();
	return executeStack.top();
}

CMDStack::~CMDStack()
{
}
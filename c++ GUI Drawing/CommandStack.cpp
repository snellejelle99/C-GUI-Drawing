#include "CommandStack.h"

CMDStack::CMDStack()
{
}

CMDStack::CMDStack(const std::stack<Command*> executeStack, const std::stack<Command*> revertStack) : executeStack(executeStack), revertStack(revertStack)
{
}

void CMDStack::Add(Command * const newCMD)
{
	newCMD->Execute();
	executeStack.push(newCMD);
}

void CMDStack::Undo()
{
	executeStack.top()->Undo();
	revertStack.push(executeStack.top());
	executeStack.pop();
}

void CMDStack::Redo()
{
	revertStack.top()->Execute();
	executeStack.push(revertStack.top());
	revertStack.pop();
}

CMDStack::~CMDStack()
{
}
#include "CommandStack.h"

CMDStack::CMDStack()
{
}

CMDStack::CMDStack(const std::stack<Command*> executeStack, const std::stack<Command*> revertStack) : executeStack(executeStack), revertStack(revertStack)
{
}

//executes command and pushes to executestack
void CMDStack::Add(Command * const newCMD)
{
	newCMD->Execute();
	executeStack.push(newCMD);
}

//pulls command from executestack undos and pushes to revertstack
void CMDStack::Undo()
{
	if (!executeStack.empty())
	{
		executeStack.top()->Undo();
		revertStack.push(executeStack.top());
		executeStack.pop();
	}
}

//pulls command from revertstack undos and pushes to executestack
void CMDStack::Redo()
{
	if (!revertStack.empty())
	{
		revertStack.top()->Execute();
		executeStack.push(revertStack.top());
		revertStack.pop();
	}
}

//empties the commandstack
void CMDStack::Flush()
{
	executeStack = std::stack<Command*>();
	revertStack = std::stack<Command*>();
}

CMDStack::~CMDStack()
{
}
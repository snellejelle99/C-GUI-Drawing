#pragma once
class Command
{
public:
	virtual void Execute() = 0;

	virtual void undo() = 0;
};


#pragma once

#include <cstddef>

#include "KeyboardCommand.h"

class CommandInputStream
{
public:
	virtual std::size_t getCommandsPending(void) const = 0;
	
	virtual KeyboardCommand peekCommand(void) const = 0;
	virtual KeyboardCommand readCommand(void) = 0;
	
	virtual bool hasCommandsPending(void) const
	{
		return (this->getCommandsPending() > 0);
	}
};
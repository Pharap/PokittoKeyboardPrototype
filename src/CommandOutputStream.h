#pragma once

#include <cstddef>

#include "KeyboardCommand.h"

class CommandOutputStream
{
public:
	virtual std::size_t getCommandsPending(void) const = 0;
	
	virtual void emitCommand(KeyboardCommand command) = 0;
	
	virtual void flush(void)
	{
	}
	
	virtual bool hasCommandsPending(void) const
	{
		return (this->getCommandsPending() > 0);
	}
};
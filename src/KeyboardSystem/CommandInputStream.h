#pragma once

#include <cstddef>

#include "KeyboardCommand.h"

template< typename CharT >
class CommandInputStream
{
public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;

public:
	virtual std::size_t getReadsPending(void) const = 0;
	
	virtual bool hasReadsPending(void) const
	{
		return (this->getReadsPending() > 0);
	}

	virtual bool canRead(void) const
	{
		return this->hasReadsPending();
	}
	
	virtual command_type peekCommand(void) const = 0;

	virtual void dropCommand(void) = 0;

	virtual command_type readCommand(void)
	{
		const auto result = this->peekCommand();
		this->dropCommand();
	}
};
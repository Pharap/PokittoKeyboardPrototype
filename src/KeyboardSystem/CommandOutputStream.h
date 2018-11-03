#pragma once

#include <cstddef>

#include "KeyboardCommand.h"

template< typename CharT >
class CommandOutputStream
{
public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;

public:
	virtual std::size_t getWritesPending(void) const
	{
		return 0;
	}
	
	virtual bool hasWritesPending(void) const
	{
		return (this->getWritesPending() > 0);
	}

	virtual bool canWrite(void) const
	{
		return true;
	}
	
	virtual void writeCommand(command_type command) = 0;
	
	virtual void flush(void)
	{
	}
};
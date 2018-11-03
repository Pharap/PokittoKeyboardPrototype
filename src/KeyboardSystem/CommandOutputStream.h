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
	virtual std::size_t getCommandsPending(void) const = 0;
	
	virtual void emitCommand(command_type command) = 0;
	
	virtual void flush(void)
	{
	}
	
	virtual bool hasCommandsPending(void) const
	{
		return (this->getCommandsPending() > 0);
	}
};

using BasicCommandOutputStream = CommandOutputStream<char>;
using WideCommandOutputStream = CommandOutputStream<wchar_t>;
using UTF16CommandOutputStream = CommandOutputStream<char32_t>;
using UTF32CommandOutputStream = CommandOutputStream<char32_t>;

using CommonCommandOutputStream = UTF32CommandOutputStream;
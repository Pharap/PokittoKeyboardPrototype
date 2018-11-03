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
	virtual std::size_t getCommandsPending(void) const = 0;
	
	virtual command_type peekCommand(void) const = 0;
	virtual command_type readCommand(void) = 0;
	
	virtual bool hasCommandsPending(void) const
	{
		return (this->getCommandsPending() > 0);
	}
};

using BasicCommandInputStream = CommandInputStream<char>;
using WideCommandInputStream = CommandInputStream<wchar_t>;
using UTF16CommandInputStream = CommandInputStream<char32_t>;
using UTF32CommandInputStream = CommandInputStream<char32_t>;

using CommonCommandInputStream = UTF32CommandInputStream;
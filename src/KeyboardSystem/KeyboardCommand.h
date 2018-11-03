#pragma once

#include "KeyboardCommandType.h"

template< typename CharT >
struct KeyboardCommand
{
	using char_type = CharT;

	KeyboardCommandType type = KeyboardCommandType::None;
	char_type character = '\0';
	
	constexpr KeyboardCommand(void) = default;
	
	constexpr KeyboardCommand(KeyboardCommandType type)
		: type(type), character('\0')
	{
	}
	
	constexpr KeyboardCommand(char_type character)
		: type(KeyboardCommandType::Char), character(character)
	{
	}
	
	constexpr KeyboardCommand(KeyboardCommandType type, char_type character)
		: type(type), character(character)
	{
	}

	template< typename OtherCharT >
	constexpr explicit operator KeyboardCommand<OtherCharT>(void) const
	{
		return KeyboardCommand<OtherCharT>(this->type, static_cast<char_type>(this->character));
	}
};

using BasicCommand = KeyboardCommand<char>;
using WideCommand = KeyboardCommand<wchar_t>;
using UTF16Command = KeyboardCommand<char32_t>;
using UTF32Command = KeyboardCommand<char32_t>;

using CommonCommand = UTF32Command;
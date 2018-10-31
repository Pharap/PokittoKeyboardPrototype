#pragma once

#include "KeyboardCommandType.h"

struct KeyboardCommand
{
	KeyboardCommandType type = KeyboardCommandType::None;
	char32_t character = '\0';
	
	constexpr KeyboardCommand(void) = default;
	
	constexpr KeyboardCommand(KeyboardCommandType type)
		: type(type), character('\0')
	{
	}
	
	constexpr KeyboardCommand(char32_t character)
		: type(KeyboardCommandType::Char), character(character)
	{
	}
	
	constexpr KeyboardCommand(KeyboardCommandType type, char32_t character)
		: type(type), character(character)
	{
	}
};
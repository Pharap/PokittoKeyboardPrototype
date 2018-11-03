#pragma once

#include <Pokitto.h>

#include <array>

#include "Grid.h"
#include "CursorPosition.h"
#include "KeyboardCommand.h"
#include "CommandInputStream.h"

/*class GridKeyboard : public CommandInputStream
{
private:
	std::array<KeyboardCommand, 8> buffer;
	std::size_t next = 0;

	void push(KeyboardCommand c)
	{
		if(this->next == this->buffer.size())
			return;

		this->buffer[this->next] = c;
		++this->next;
	}

public:
	std::size_t getCommandsPending(void) const override
	{
		return this->next;
	}

	bool hasCommandsPending(void) const override
	{
		return (this->next > 0);
	}
	
	KeyboardCommand peekCommand(void) const override
	{
		if(this->next == 0)
			return KeyboardCommand();

		return this->buffer[this->next - 1];
	}

	KeyboardCommand readCommand(void) override
	{
		if(this->next == 0)
			return KeyboardCommand();

		--this->next;
		return this->buffer[this->next];
	}
}*/
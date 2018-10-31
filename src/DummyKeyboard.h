#pragma once

#include <Pokitto.h>

#include <array>

#include "Grid.h"
#include "CursorPosition.h"
#include "KeyboardCommand.h"
#include "CommandInputStream.h"

class DummyKeyboard : public CommandInputStream
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

	void update(void)
	{
		using Pokitto::Buttons;

		if(Buttons::pressed(BTN_A))
		{
			//this->push(KeyboardCommand(static_cast<char32_t>(static_cast<char>('A'))));
			this->push(KeyboardCommand(KeyboardCommandType::Char, 'A'));
		}

		if(Buttons::pressed(BTN_B))
		{
			this->push(KeyboardCommand(KeyboardCommandType::Backspace));
		}

		if(Buttons::pressed(BTN_UP))
		{
			this->push(KeyboardCommand(KeyboardCommandType::ArrowUp));
		}

		if(Buttons::pressed(BTN_DOWN))
		{
			this->push(KeyboardCommand(KeyboardCommandType::ArrowDown));
		}

		if(Buttons::pressed(BTN_LEFT))
		{
			this->push(KeyboardCommand(KeyboardCommandType::ArrowLeft));
		}

		if(Buttons::pressed(BTN_RIGHT))
		{
			this->push(KeyboardCommand(KeyboardCommandType::ArrowRight));
		}
	}
};
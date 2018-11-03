#pragma once

#include <Pokitto.h>

#include <array>

#include "../Grid.h"
#include "../KeyboardCommand.h"
#include "../CommandInputStream.h"

template< typename CharT >
class DummyKeyboard : public CommandInputStream<CharT>
{
public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;

private:
	std::array<command_type, 8> buffer;
	std::size_t next = 0;

	void push(command_type c)
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
	
	command_type peekCommand(void) const override
	{
		if(this->next == 0)
			return command_type();

		return this->buffer[this->next - 1];
	}

	command_type readCommand(void) override
	{
		if(this->next == 0)
			return command_type();

		--this->next;
		return this->buffer[this->next];
	}

	void update(void)
	{
		using Pokitto::Buttons;

		if(Buttons::pressed(BTN_A))
		{
			//this->push(command_type(static_cast<char32_t>(static_cast<char>('A'))));
			this->push(command_type(KeyboardCommandType::Char, 'A'));
		}

		if(Buttons::pressed(BTN_B))
		{
			this->push(command_type(KeyboardCommandType::Backspace));
		}

		if(Buttons::pressed(BTN_UP))
		{
			this->push(command_type(KeyboardCommandType::ArrowUp));
		}

		if(Buttons::pressed(BTN_DOWN))
		{
			this->push(command_type(KeyboardCommandType::ArrowDown));
		}

		if(Buttons::pressed(BTN_LEFT))
		{
			this->push(command_type(KeyboardCommandType::ArrowLeft));
		}

		if(Buttons::pressed(BTN_RIGHT))
		{
			this->push(command_type(KeyboardCommandType::ArrowRight));
		}
	}
};
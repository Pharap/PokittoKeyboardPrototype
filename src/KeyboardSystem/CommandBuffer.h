#pragma once

#include <cstddef>
#include <array>

#include "KeyboardCommandType.h"
#include "KeyboardCommand.h"
#include "CommandInputStream.h"
#include "CommandOutputStream.h"

template< typename CharT, std::size_t Capacity >
class CommandBuffer
	: public CommandInputStream<CharT>, public CommandOutputStream<CharT>
{
public:
	using char_type = CharT;
	using size_type = std::size_t;
	using command_type = KeyboardCommand<CharT>;
	using input_stream_type = CommandInputStream<CharT>;
	using output_stream_type = CommandOutputStream<CharT>;

public:
	static constexpr std::size_t capacity = Capacity;

private:
	std::array<command_type, capacity> buffer;
	std::size_t next = 0;

public:
	std::size_t getReadsPending(void) const override
	{
		return this->next;
	}
	
	bool hasReadsPending(void) const override
	{
		return (this->next > 0);
	}

	bool canRead(void) const override
	{
		return (this->next > 0);
	}
	
	// No need to override getWritesPending

	bool hasWritesPending(void) const override
	{
		return false;
	}

	bool canWrite(void) const override
	{
		return (this->next < this->buffer.size());
	}
	
	command_type peekCommand(void) const override
	{
		return (this->next > 0) ? this->buffer[this->next - 1] : command_type();
	}

	void dropCommand(void) override
	{
		--this->next;
	}

	command_type readCommand(void) override
	{
		if (this->next == 0)
			return command_type();

		--this->next;
		return this->buffer[next];
	}
	
	void writeCommand(command_type command) override
	{
		if(this->next < this->buffer.size())
		{
			this->buffer[next] = command;
			++this->next;
		}
	}
};
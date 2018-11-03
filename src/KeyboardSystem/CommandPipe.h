#pragma once

#include "KeyboardCommand.h"
#include "CommandInputStream.h"
#include "CommandOutputStream.h"

template< typename CharT >
class CommandPipe
{
public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;
	using input_stream_type = CommandInputStream<CharT>;
	using output_stream_type = CommandOutputStream<CharT>;

private:
	input_stream_type * input = nullptr;
	output_stream_type * output = nullptr;

public:
	constexpr CommandPipe(void) = default;

	constexpr CommandPipe(input_stream_type & input)
		: input(&input), output(nullptr)
	{
	}

	constexpr CommandPipe(output_stream_type & output)
		: input(nullptr), output(&output)
	{
	}

	constexpr CommandPipe(input_stream_type & input, output_stream_type & output)
		: input(&input), output(&output)
	{
	}

	void update(void)
	{
		if(input != nullptr)
		{
			if(output != nullptr)
			{
				while(input->hasCommandsPending())
				{
					auto command = input->readCommand();
					output->emitCommand(command);
				}

				while(output->hasCommandsPending())
					output->flush();
			}
			else
			{
				while(input->hasCommandsPending())
					(void)input->readCommand();
			}
		}
	}
};
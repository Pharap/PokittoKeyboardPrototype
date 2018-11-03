#pragma once

#include "KeyboardCommand.h"
#include "CommandInputStream.h"
#include "CommandOutputStream.h"

template< typename CharInT, typename CharOutT >
class CommandConversionPipe
{
public:
	using char_in_type = CharInT;
	using char_out_type = CharOutT;
	using command_in_type = KeyboardCommand<CharInT>;
	using command_out_type = KeyboardCommand<CharOutT>;
	using input_stream_type = CommandInputStream<CharInT>;
	using output_stream_type = CommandOutputStream<CharOutT>;

private:
	input_stream_type * input = nullptr;
	output_stream_type * output = nullptr;

public:
	constexpr CommandConversionPipe(void) = default;

	constexpr CommandConversionPipe(input_stream_type & input)
		: input(&input), output(nullptr)
	{
	}

	constexpr CommandConversionPipe(output_stream_type & output)
		: input(nullptr), output(&output)
	{
	}

	constexpr CommandConversionPipe(input_stream_type & input, output_stream_type & output)
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
					output->emitCommand(static_cast<command_out_type>(command));
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
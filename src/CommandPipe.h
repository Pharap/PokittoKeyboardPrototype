#pragma once

#include "KeyboardCommand.h"
#include "CommandInputStream.h"
#include "CommandOutputStream.h"

class CommandPipe
{
private:
	CommandInputStream * input = nullptr;
	CommandOutputStream * output = nullptr;

public:
	constexpr CommandPipe(void) = default;

	constexpr CommandPipe(CommandInputStream & input)
		: input(&input), output(nullptr)
	{
	}

	constexpr CommandPipe(CommandOutputStream & output)
		: input(nullptr), output(&output)
	{
	}

	constexpr CommandPipe(CommandInputStream & input, CommandOutputStream & output)
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
					auto command = input->readCommand();
			}
		}
	}
};
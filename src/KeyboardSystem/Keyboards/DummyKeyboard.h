#pragma once

#include <Pokitto.h>

#include <array>

#include "../Grid.h"
#include "../KeyboardCommand.h"
#include "../CommandInputStream.h"

template< typename CharT >
class DummyKeyboard
{
public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;
	using output_stream_type = CommandOutputStream<CharT>;

private:
	output_stream_type * outputStream = nullptr;

public:
	DummyKeyboard(void) = default;

	DummyKeyboard(output_stream_type & outputStream)
		: outputStream(&outputStream)
	{
	}

	const output_stream_type * getOutput(void) const
	{
		return this->outputStream;
	}

	void setOutput(output_stream_type & outputStream)
	{
		this->outputStream = &outputStream;
	}

	void update(void)
	{
		using Pokitto::Buttons;

		if(outputStream == nullptr)
			return;

		if(!outputStream->canWrite())
			return;

		if(Buttons::pressed(BTN_A))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::Char, 'A'));
		}

		if(Buttons::pressed(BTN_B))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::Backspace));
		}

		if(Buttons::pressed(BTN_UP))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::ArrowUp));
		}

		if(Buttons::pressed(BTN_DOWN))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::ArrowDown));
		}

		if(Buttons::pressed(BTN_LEFT))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::ArrowLeft));
		}

		if(Buttons::pressed(BTN_RIGHT))
		{
			this->outputStream->writeCommand(command_type(KeyboardCommandType::ArrowRight));
		}
	}
};
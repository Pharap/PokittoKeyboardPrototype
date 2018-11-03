#pragma once

#include <Pokitto.h>

#include <cstddef>
#include <array>

#include "../Grid.h"
#include "../CursorPosition.h"
#include "../KeyboardCommand.h"
#include "../CommandInputStream.h"

template< typename CharT, std::size_t Width, std::size_t Height >
class GridKeyboard
{
public:
	static constexpr std::size_t width = Width;
	static constexpr std::size_t height = Height;

public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;
	using output_stream_type = CommandOutputStream<CharT>;
	using grid_type = Grid<command_type, width, height>;

private:
	grid_type grid;
	CursorPosition cursor;
	output_stream_type * outputStream = nullptr;

public:
	GridKeyboard(void) = default;

	GridKeyboard(output_stream_type & outputStream)
		: outputStream(&outputStream)
	{
	}

	template< std::size_t Columns, std::size_t Rows >
	GridKeyboard(const command_type (&data)[Rows][Columns])
		: grid(data)
	{
	}

	template< std::size_t Columns, std::size_t Rows >
	GridKeyboard(const command_type (&data)[Rows][Columns], output_stream_type & outputStream)
		: grid(data), outputStream(&outputStream)
	{
	}

	grid_type & getGrid(void)
	{
		return this->grid;
	}

	const grid_type & getGrid(void) const
	{
		return this->grid;
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

		if(Buttons::pressed(BTN_UP))
		{
			this->moveCursorUp();
		}

		if(Buttons::pressed(BTN_DOWN))
		{
			this->moveCursorDown();
		}

		if(Buttons::pressed(BTN_RIGHT))
		{
			this->moveCursorRight();
		}

		if(Buttons::pressed(BTN_LEFT))
		{
			this->moveCursorLeft();
		}

		if(Buttons::pressed(BTN_A))
		{
			this->sendCommand();
		}
	}

	void draw(int x, int y)
	{
		using Pokitto::Display;

		for(std::size_t j = 0; j < this->grid.getHeight(); ++j)
		{
			for(std::size_t i = 0; i < this->grid.getWidth(); ++i)
			{
				const auto command = this->grid.get(i, j);
				if(command.type == KeyboardCommandType::Char)
					Display::print_char(x + (i * Display::fontWidth), y + (j * Display::fontHeight), command.character);
			}
		}

		Display::drawRectangle(x - 1 + (this->cursor.x * Display::fontWidth), y - 1 + (this->cursor.y * Display::fontHeight), Display::fontWidth + 2, Display::fontHeight + 2);
		//Display::drawFastVLine(x + (this->cursor.x * Display::fontWidth), y + (this->cursor.y * Display::fontHeight), Display::fontHeight);
	}

private:
	void sendCommand(void)
	{
		if(this->outputStream != nullptr)
			if(this->outputStream->canWrite())
				this->outputStream->writeCommand(this->grid.get(this->cursor.x, this->cursor.y));
	}

	bool canMoveCursorUp(void) const
	{
		return (this->cursor.y > this->grid.getFirstY());
	}

	void moveCursorUp(void)
	{
		if(this->canMoveCursorUp())
			--this->cursor.y;
	}

	bool canMoveCursorDown(void) const
	{
		return (this->cursor.y < this->grid.getLastY());
	}

	void moveCursorDown(void)
	{
		if(this->canMoveCursorDown())
			++this->cursor.y;
	}
	
	bool canMoveCursorRight(void) const
	{
		return (this->cursor.x < this->grid.getLastX());
	}

	void moveCursorRight(void)
	{
		if(this->canMoveCursorRight())
			++this->cursor.x;
	}

	bool canMoveCursorLeft(void) const
	{
		return (this->cursor.x > this->grid.getFirstX());
	}

	void moveCursorLeft(void)
	{
		if(this->canMoveCursorLeft())
			--this->cursor.x;
	}
};
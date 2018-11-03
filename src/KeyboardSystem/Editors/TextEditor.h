#pragma once

#include <Pokitto.h>

#include "../Grid.h"
#include "../KeyboardCommand.h"
#include "../CommandInputStream.h"
#include "../CursorPosition.h"

template< typename CharT, std::size_t Width, std::size_t Height >
class TextEditor
{
public:
	static constexpr std::size_t width = Width;
	static constexpr std::size_t height = Height;

public:
	using char_type = CharT;
	using command_type = KeyboardCommand<CharT>;
	using input_stream_type = CommandInputStream<CharT>;
	using grid_type = Grid<CharT, width, height>;

private:
	grid_type grid;
	CursorPosition cursor;
	input_stream_type * inputStream = nullptr;

public:
	TextEditor(void) = default;

	TextEditor(input_stream_type & inputStream)
		: inputStream(&inputStream)
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

	const input_stream_type * getInput(void) const
	{
		return this->inputStream;
	}

	void setInput(input_stream_type & inputStream)
	{
		this->inputStream = &inputStream;
	}

	void update(void)
	{
		if(this->inputStream != nullptr)
			while(inputStream->hasReadsPending())
			{
				const auto command = inputStream->readCommand();
				this->handleCommand(command);
			}
	}

	void draw(int x, int y)
	{
		using Pokitto::Display;

		for(std::size_t j = 0; j < this->grid.getHeight(); ++j)
		{
			for(std::size_t i = 0; i < this->grid.getWidth(); ++i)
			{
				const auto c = this->grid.get(i, j);
				Display::print_char(x + (i * Display::fontWidth), y + (j * Display::fontHeight), c);
			}
		}

		//Display::drawRectangle(x - 2 + (this->cursor.x * Display::fontWidth), y + (this->cursor.y * Display::fontHeight), Display::fontWidth, Display::fontHeight);
		Display::drawFastVLine(x + (this->cursor.x * Display::fontWidth), y + (this->cursor.y * Display::fontHeight), Display::fontHeight);
	}

private:
	void handleCommand(command_type command)
	{
		switch(command.type)
		{
			case KeyboardCommandType::None:
				break;
			case KeyboardCommandType::Char:
				this->insertChar(command.character);
				this->advanceCursor();
				break;
			case KeyboardCommandType::ArrowUp:
				this->moveCursorUp();
				break;
			case KeyboardCommandType::ArrowDown:
				this->moveCursorDown();
				break;
			case KeyboardCommandType::ArrowLeft:
				this->moveCursorLeft();
				break;
			case KeyboardCommandType::ArrowRight:
				this->moveCursorRight();
				break;
			case KeyboardCommandType::Backspace:
				this->reatreatCursor();
				this->insertChar('\0');
				break;
			case KeyboardCommandType::Enter:
				break;
			case KeyboardCommandType::Tab:
				break;
			case KeyboardCommandType::Control:
				break;
			case KeyboardCommandType::Alt:
				break;
			case KeyboardCommandType::AltGr:
				break;
			case KeyboardCommandType::Escape:
				break;
			case KeyboardCommandType::Insert:
				break;
			case KeyboardCommandType::Delete:
				break;
			case KeyboardCommandType::Home:
				this->moveCursorToLineStart();
				break;
			case KeyboardCommandType::End:
				this->moveCursorToLineEnd();
				break;
			case KeyboardCommandType::PageUp:
				break;
			case KeyboardCommandType::PageDown:
				break;
			case KeyboardCommandType::F1:
				break;
			case KeyboardCommandType::F2:
				break;
			case KeyboardCommandType::F3:
				break;
			case KeyboardCommandType::F4:
				break;
			case KeyboardCommandType::F5:
				break;
			case KeyboardCommandType::F6:
				break;
			case KeyboardCommandType::F7:
				break;
			case KeyboardCommandType::F8:
				break;
			case KeyboardCommandType::F9:
				break;
			case KeyboardCommandType::F10:
				break;
			case KeyboardCommandType::F11:
				break;
			case KeyboardCommandType::F12:
				break;
		}
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

	void insertChar(char_type character)
	{
		this->grid.set(this->cursor.x, this->cursor.y, character);
	}

	void overwriteChar(char_type character)
	{
		this->advanceCursor();
		this->insertChar(character);
	}

	void moveCursorToLineStart(void)
	{
		this->cursor.x = this->grid.getFirstX();
	}

	void moveCursorToLineEnd(void)
	{
		this->cursor.x = this->grid.getLastX();
	}

	void advanceCursor(void)
	{
		if(this->canMoveCursorRight())
		{
			++this->cursor.x;
		}
		else if(this->canMoveCursorDown())
		{
			this->cursor.x = this->grid.getFirstX();
			++this->cursor.y;
		}
	}

	void reatreatCursor(void)
	{
		if(this->canMoveCursorLeft())
		{
			--this->cursor.x;
		}
		else if(this->canMoveCursorUp())
		{
			this->cursor.x = this->grid.getLastX();
			--this->cursor.y;
		}
	}
};
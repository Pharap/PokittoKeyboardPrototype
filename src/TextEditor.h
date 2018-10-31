#pragma once

#include <Pokitto.h>

#include "Grid.h"
#include "CursorPosition.h"
#include "KeyboardCommand.h"
#include "CommandOutputStream.h"

class TextEditor : public CommandOutputStream
{
private:
	using TextGrid = Grid<char, 24, 12>;

private:
	TextGrid text;
	CursorPosition cursor = CursorPosition(0, 0);

public:
	std::size_t getCommandsPending(void) const override
	{
		return 0;
	}

	bool hasCommandsPending(void) const override
	{
		return false;
	}
	
	void emitCommand(KeyboardCommand command) override
	{
		switch(command.type)
		{
			case KeyboardCommandType::None:
				break;
			case KeyboardCommandType::Char:
				this->text.set(this->cursor.x, this->cursor.y, static_cast<char>(command.character));

				++this->cursor.x;
				if(this->cursor.x == text.getWidth())
				{
					this->cursor.x = 0;
					++this->cursor.y;
				}
				break;
			case KeyboardCommandType::ArrowUp:
				if(this->cursor.y > 0)
					--this->cursor.y;
				break;
			case KeyboardCommandType::ArrowDown:
				if(this->cursor.y < (this->text.getHeight() - 1))
					++this->cursor.y;
				break;
			case KeyboardCommandType::ArrowLeft:
				if(this->cursor.x > 0)
					--this->cursor.x;
				break;
			case KeyboardCommandType::ArrowRight:
				if(this->cursor.x < (this->text.getWidth() - 1))
					++this->cursor.x;
				break;
			case KeyboardCommandType::Backspace:
				if(this->cursor.x > 0)
					--this->cursor.x;
				else
				{
					this->cursor.x = 0;
					if(this->cursor.y > 0)
						--this->cursor.y;
				}
				this->text.set(this->cursor.x, this->cursor.y, ' ');
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
				this->cursor.x = 0;
				break;
			case KeyboardCommandType::End:
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

	void draw(int x, int y)
	{
		using Pokitto::Display;

		for(std::size_t j = 0; j < this->text.getHeight(); ++j)
		{
			for(std::size_t i = 0; i < this->text.getWidth(); ++i)
			{
				const auto c = this->text.get(i, j);
				Display::print_char(x + (i * Display::fontWidth), y + (j * Display::fontHeight), c);
			}
		}

		//Display::drawRectangle(x - 2 + (this->cursor.x * Display::fontWidth), y + (this->cursor.y * Display::fontHeight), Display::fontWidth, Display::fontHeight);
		Display::drawFastVLine(x + (this->cursor.x * Display::fontWidth), y + (this->cursor.y * Display::fontHeight), Display::fontHeight);
	}
};
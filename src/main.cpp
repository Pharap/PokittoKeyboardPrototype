#define DISABLEAVRMIN
#include <Pokitto.h>

#include "KeyboardSystem.h"

BasicCommand commands[3][13] =
{
	{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'},
	{'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
	{
		KeyboardCommandType::ArrowUp,
		KeyboardCommandType::ArrowDown,
		KeyboardCommandType::ArrowLeft,
		KeyboardCommandType::ArrowRight,
		KeyboardCommandType::Backspace,
		KeyboardCommandType::Delete,
		KeyboardCommandType::Home,
		KeyboardCommandType::End,
		KeyboardCommandType::Enter,
		KeyboardCommandType::PageUp,
		KeyboardCommandType::PageDown,
		KeyboardCommandType::Tab,
		KeyboardCommandType::Escape,
	},
};

CommandBuffer<char, 8> buffer;
TextEditor<char, 12, 12> editor = { buffer };
GridKeyboard<char, 13, 3> keyboard = { commands, buffer };

int main ()
{
	using Pokitto::Core;
	using Pokitto::Display;
	using Pokitto::Buttons;

	Core::begin();

	//auto pipe = CommandConversionPipe<char32_t, char>(keyboard, editor);

	
	//constexpr std::size_t yLimit = 3;
	//constexpr std::size_t xLimit = 13;

	/*for(std::size_t y = 0; y < yLimit; ++y)
		for(std::size_t x = 0; x < xLimit; ++x)
			keyboard.getGrid().set(x, y, commands[y][x]);*/

	while (Core::isRunning())
	{
		if (Core::update())
		{
			keyboard.update();
			editor.update();

			editor.draw(0, 0);
			keyboard.draw(0, 100);
		}
	}
}
#define DISABLEAVRMIN
#include <Pokitto.h>

#include "KeyboardSystem.h"

TextEditor<char> editor;
DummyKeyboard<char32_t> keyboard;

int main ()
{
	using Pokitto::Core;
	using Pokitto::Display;
	using Pokitto::Buttons;

	Core::begin();

	auto pipe = CommandConversionPipe<char32_t, char>(keyboard, editor);

	while (Core::isRunning())
	{
		if (Core::update())
		{
			keyboard.update();
			pipe.update();
			editor.draw(0, 0);
		}
	}
}
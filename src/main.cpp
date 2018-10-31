#define DISABLEAVRMIN
#include <Pokitto.h>

#include "TextEditor.h"
#include "DummyKeyboard.h"
#include "CommandPipe.h"

TextEditor editor;
DummyKeyboard keyboard;

int main ()
{
	using Pokitto::Core;
	using Pokitto::Display;
	using Pokitto::Buttons;

	Core::begin();

	auto pipe = CommandPipe(keyboard, editor);

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
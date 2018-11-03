#pragma once

#include "KeyboardCommand.h"

using BasicCommand = KeyboardCommand<char>;
using WideCommand = KeyboardCommand<wchar_t>;
using UTF16Command = KeyboardCommand<char32_t>;
using UTF32Command = KeyboardCommand<char32_t>;

#include "CommandInputStream.h"

using BasicCommandInputStream = CommandInputStream<char>;
using WideCommandInputStream = CommandInputStream<wchar_t>;
using UTF16CommandInputStream = CommandInputStream<char32_t>;
using UTF32CommandInputStream = CommandInputStream<char32_t>;

#include "CommandOutputStream.h"

using BasicCommandOutputStream = CommandOutputStream<char>;
using WideCommandOutputStream = CommandOutputStream<wchar_t>;
using UTF16CommandOutputStream = CommandOutputStream<char32_t>;
using UTF32CommandOutputStream = CommandOutputStream<char32_t>;

#include "CommandPipe.h"

using BasicCommandPipe = CommandPipe<char>;
using WideCommandPipe = CommandPipe<wchar_t>;
using UTF16CommandPipe = CommandPipe<char32_t>;
using UTF32CommandPipe = CommandPipe<char32_t>;
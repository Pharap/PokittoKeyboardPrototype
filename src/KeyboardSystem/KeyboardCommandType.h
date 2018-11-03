#pragma once

#include <cstdint>

enum class KeyboardCommandType : std::uint8_t
{
	// Does nothing
	None = 0x00,
	
	// Character
	Char = 0x01,
	
	// Arrow keys
	ArrowUp = 0x10,
	ArrowDown = 0x11,
	ArrowLeft = 0x12,
	ArrowRight = 0x13,
	
	Backspace = 0x14,
	Enter = 0x15,
	
	Tab = 0x16,
	//CapsLock = 0x17
	
	Control = 0x18,
	Alt = 0x19,
	AltGr = 0x1A,
	
	Escape = 0x1F,
	
	// Grouping of 6
	Insert = 0x20,
	Delete = 0x21,
	Home = 0x22,
	End = 0x23,
	PageUp = 0x24,
	PageDown = 0x25,
	
	// Function keys
	F1 = 0xF1,
	F2 = 0xF2,
	F3 = 0xF3,
	F4 = 0xF4,
	F5 = 0xF5,
	F6 = 0xF6,
	F7 = 0xF7,
	F8 = 0xF8,
	F9 = 0xF9,
	F10 = 0xFA,
	F11 = 0xFB,
	F12 = 0xFC,
};
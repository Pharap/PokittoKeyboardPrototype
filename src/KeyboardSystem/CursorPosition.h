#pragma once

#include <cstddef>

struct CursorPosition
{
	std::size_t x;
	std::size_t y;

	CursorPosition(void) = default;
	constexpr CursorPosition(std::size_t x, std::size_t y)
		: x(x), y(y)
	{
	}
};
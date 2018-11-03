#pragma once

#include <cstddef>
#include <array>

template< typename T , std::size_t Width, std::size_t Height >
class Grid
{
public:
	using value_type = T;
	using size_type = std::size_t;
	static constexpr size_type width = Width;
	static constexpr size_type height = Height;
	static constexpr size_type capacity = width * height;

private:
	std::array<value_type, capacity> characters;

	static constexpr size_type getIndex(size_type x, size_type y)
	{
		return x + (y * width);
	}

public:
	constexpr size_type getWidth(void) const
	{
		return width;
	}

	constexpr size_type getHeight(void) const
	{
		return height;
	}

	value_type get(size_type x, size_type y) const
	{
		return characters[getIndex(x, y)];
	}

	void set(size_type x, size_type y, value_type value)
	{
		characters[getIndex(x, y)] = value;
	}
};
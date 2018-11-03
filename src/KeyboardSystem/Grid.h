#pragma once

#include <cstddef>
#include <array>

template< typename T , std::size_t Width, std::size_t Height >
class Grid
{
public:
	using value_type = T;
	using size_type = std::size_t;

public:
	static constexpr size_type width = Width;
	static constexpr size_type height = Height;
	static constexpr size_type capacity = width * height;

private:
	std::array<value_type, capacity> data;

	static constexpr size_type getIndex(size_type x, size_type y)
	{
		return x + (y * width);
	}

public:
	constexpr Grid(void) = default;
	
	template< std::size_t Columns, std::size_t Rows >
	Grid(const T (&data)[Rows][Columns])
	{
		constexpr std::size_t yLimit = (Rows < height) ? Rows : height;
		constexpr std::size_t xLimit = (Columns < width) ? Columns : width;

		for(std::size_t y = 0; y < yLimit; ++y)
			for(std::size_t x = 0; x < xLimit; ++x)
				this->data[getIndex(x, y)] = data[y][x];
	}

	constexpr size_type getWidth(void) const
	{
		return width;
	}

	constexpr size_type getHeight(void) const
	{
		return height;
	}

	constexpr size_type getFirstX(void) const
	{
		return 0;
	}

	constexpr size_type getLastX(void) const
	{
		return (width - 1);
	}

	constexpr size_type getFirstY(void) const
	{
		return 0;
	}

	constexpr size_type getLastY(void) const
	{
		return (height - 1);
	}

	value_type get(size_type x, size_type y) const
	{
		return this->data[getIndex(x, y)];
	}

	void set(size_type x, size_type y, value_type value)
	{
		this->data[getIndex(x, y)] = value;
	}
};
#ifndef BASE_MAPPER_H
#define BASE_MAPPER_H

#include <iostream>
#include <thread>
#include <chrono>

struct attrib
{
	uint16_t offset;
	uint8_t count, format;
};

template<typename H> class base_mapper
{
protected:
	uint16_t f, b;

	void wait_for_size()
	{
		uint32_t* beg = (uint32_t*)((uint8_t*)this + sizeof(uint32_t));
		uint32_t* end = (uint32_t*)((uint8_t*)this + sizeof(H));

		while (!*beg);

		while (beg < end)
		{
			f += (*beg >> 0b10000) & 0xFF;
			++beg;
		}

		b = f << 0b10;
	}

	base_mapper() : f(0), b(0)
	{
		std::thread t(&base_mapper::wait_for_size, this);
		t.detach();
	}

public:
	static const H i;

	inline uint16_t float_per_vert() const
	{
		return f;
	}

	inline uint16_t byte_per_vert() const
	{
		return b;
	}
};

template<typename H> const H base_mapper<H>::i;

#endif

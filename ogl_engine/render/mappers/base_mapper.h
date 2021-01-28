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
	uint16_t b, f;
	uint32_t ac;

	void wait_for_size()
	{
		attrib* beg = (attrib*)((uint8_t*)this + sizeof(uint64_t));
		attrib* end = (attrib*)((uint8_t*)this + sizeof(H));

		ac = end - beg;

		while (!*(uint32_t*)beg);

		while (beg < end)
		{
			f += beg->count;
			++beg;
		}

		b = f << 0b10;
	}

	base_mapper() : f(0)
	{
		std::thread t(&base_mapper::wait_for_size, this);
		t.detach();
	}

public:
	static const H i;

	inline attrib* data() const
	{
		return (attrib*)((uint8_t*)this + sizeof(uint64_t));
	}

	inline uint32_t attrib_count() const
	{
		return ac;
	}

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

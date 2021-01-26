#ifndef VBO_H
#define	VBO_H

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "mappers/base_mapper.h"

static const char* str_formats[] = { "%08X", "%f", "%d" };
enum : uint8_t {X, Y, Z, W};

template<typename M, typename std::enable_if<std::is_base_of<base_mapper<M>, M>::value>::type* = nullptr>
class vbo
{
public:
	class vertex;

private:
	std::vector<uint8_t> buffer;
	std::vector<vertex>	 vertices;

	GLuint		vao, vbo;
	uint32_t	populated;
	uint8_t*	first_gap;

	uint32_t primitive_type;

	//shader shd;

public:

	class vertex
	{
	private:
		vbo* b;
		uint8_t* p;

		vertex(vbo* _b) : b(_b), p(nullptr) {}

		inline void set_ptr(uint8_t* _p)
		{
			p = _p;
		}

		inline uint32_t convert_offset(attrib _attrib, uint8_t _comp, uint8_t _byte)
		{
			return
				((_attrib.offset % M::i.float_per_vert()) << 0b10) +
				((_comp % _attrib.count) << 0b10) +
				(_byte % 0b100);
		}

		inline uint8_t convert_offset_flag(uint8_t _bit)
		{
			return _bit % 0b1000;
		}

	public:
		template<typename T> inline void set(const T& _val, const attrib _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			uint8_t* d = p + convert_offset(_attrib, _comp, _byte);
			uint32_t s = sizeof(T);

			memcpy(d, &_val, s);

			glBufferSubData(GL_ARRAY_BUFFER, d - b->buffer.data(), s, &_val);
		}

		template<typename T> inline void set(const T&& _val, const attrib _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			set(_val, _attrib, _comp, _byte);
		}

		template<typename T> inline T get(const attrib _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			return *(T*)(p + convert_offset(_attrib, _comp, _byte));
		}

		inline void set_flag(bool _val, const attrib _attrib, uint8_t _comp = 0, uint8_t _byte = 0, uint8_t _bit = 0)
		{
			uint8_t o = convert_offset_flag(_bit);
			uint8_t t = get<uint8_t>(_attrib, _comp, _byte);
			uint8_t m = ~(1 << o);

			set<uint8_t>((t & m) | (_val << o), _attrib, _comp, _byte);
		}

		inline bool get_flag(const attrib _attrib, uint8_t _comp = 0, uint8_t _byte = 0, uint8_t _bit = 0)
		{
			return get<uint8_t>(_attrib, _comp, _byte) & (1 << convert_offset_flag(_bit));
		}

		inline void free()
		{
			if (p < b->first_gap) b->first_gap = p;
			p = nullptr;
		}

		friend class vbo;
	};

	vbo(uint32_t _vc)
		: populated(-M::i.byte_per_vert()), first_gap(nullptr)
	{
		buffer.resize(M::i.byte_per_vert() * _vc);
		vertices.resize(_vc, this);

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		bind();

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, buffer.size(), buffer.data(), GL_STREAM_DRAW);

		attrib att;
		uint32_t end = sizeof(M) >> 0b10;

		for (uint32_t j = 0, i = 1; i != end; ++j, ++i)
		{
			att = *((attrib*)&M::i + i);
			glVertexAttribPointer(
				j,
				att.count,
				GL_FLOAT,
				false,
				M::i.byte_per_vert(),
				(const void*)((att.offset) << 0b10)
			);
			glEnableVertexAttribArray(j);
		}

		unbind();
	}

	inline void bind()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	inline void unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline void set_primitive_type(uint32_t _primitive_type)
	{
		primitive_type = _primitive_type;
	}

	virtual ~vbo()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
};

#endif

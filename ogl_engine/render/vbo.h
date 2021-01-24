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
	uint32_t	populated, first_gap;

	uint16_t primitive_type;

	//shader shd;

public:

	class vertex
	{
	private:
		uint8_t* p;

		vertex(uint8_t* _p) : p(_p) {}

		inline uint32_t convert_offset(uint32_t _attrib, uint8_t _comp, uint8_t _byte)
		{
			return
				(((_attrib & 0xFFFF) % M::i.float_per_vert()) << 0b10) +
				((_comp % ((_attrib >> 0b10000) & 0xFF)) << 0b10) +
				(_byte % 0b100);
		}

		inline uint8_t convert_offset_flag(uint8_t _bit)
		{
			return _bit % 0b1000;
		}

	public:
		template<typename T> inline void set(const T& _val, uint32_t _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			memcpy(p + convert_offset(_attrib, _comp, _byte), &_val, sizeof(T));
		}

		template<typename T> inline void set(const T&& _val, uint32_t _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			set(_val, _attrib, _comp, _byte);
		}

		template<typename T> inline T get(uint32_t _attrib, uint8_t _comp = 0, uint8_t _byte = 0)
		{
			return *(T*)(p + convert_offset(_attrib, _comp, _byte));
		}

		void set_flag(bool _val, uint32_t _attrib, uint8_t _comp = 0, uint8_t _byte = 0, uint8_t _bit = 0)
		{
			uint8_t o = convert_offset_flag(_bit);
			uint8_t t = get<uint8_t>(_attrib, _comp, _byte);
			uint8_t m = ~(1 << o);

			set<uint8_t>((t & m) | (_val << o), _attrib, _comp, _byte);
		}

		bool get_flag(uint32_t _attrib, uint8_t _comp = 0, uint8_t _byte = 0, uint8_t _bit = 0)
		{
			return get<uint8_t>(_attrib, _comp, _byte) & (1 << convert_offset_flag(_bit));
		}

		void free()
		{
			p = nullptr;
		}

		friend class vbo;
	};

	vbo(uint32_t _vc)
	{
		//buffer = ByteBuffer.allocateDirect(bytesPerVert() * (1 << shift)).order(ByteOrder.nativeOrder());
		buffer.resize(M::i.byte_per_vert() * _vc);
		//vertices = new ArrayList<>();
		vertices.resize(_vc);

		//populated = -bytesPerVert();
		//firstGap = 0x7FFFFFFF;

		//vertices.add(new Vertex());

		//vao = glGenVertexArrays();
		//vbo = glGenBuffers();
		//bind();
		//glBufferData(GL_ARRAY_BUFFER, buffer.capacity(), GL_STREAM_DRAW);

		//fillAttribs();
		//setDataTypes();
		//setFormats();

		//for (int i = 0; i < attribOffsets.length - 1; ++i) {
		//	//            if (isInt(dataTypes[i]))
		//	//                glVertexAttribIPointer(i, attribOffsets[i + 1] - attribOffsets[i], dataTypes[i], bytesPerVert(), attribOffsets[i] << 2);
		//	//            else
		//	//                glVertexAttribPointer(i, attribOffsets[i + 1] - attribOffsets[i], dataTypes[i], false, bytesPerVert(), attribOffsets[i] << 2);

		//	glVertexAttribPointer(i, attribOffsets[i + 1] - attribOffsets[i], GL_FLOAT, false, bytesPerVert(), attribOffsets[i] << 2);
		//	glEnableVertexAttribArray(i);
		//}
	}
};

#endif

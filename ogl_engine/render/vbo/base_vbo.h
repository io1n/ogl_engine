#ifndef BASE_VBO_H
#define BASE_VBO_H

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

enum : uint8_t { X, Y, Z, W };

class base_vbo
{
protected:
	static void (*const print_func[])(void*);

	std::vector<uint8_t> buffer;

	GLuint		vao, vbo;
	GLenum		primitive_type;
	uint32_t	populated;
	uint8_t*	first_gap;

	//shader* shd;

public:
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

	inline void set_primitive_type(GLenum _primitive_type)
	{
		primitive_type = _primitive_type;
	}

	void draw()
	{
		bind();
		//shd->enable();
		glDrawArrays(primitive_type, 0, populated);
		//shd->disable();
		unbind();
	}

	virtual void show() = 0;

	virtual ~base_vbo()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
};

void (*const base_vbo::print_func[])(void*) =
{
	[](void* p) { printf("%08X",*(uint32_t*)p); },
	[](void* p) { printf("%f",	*(float*)p); },
	[](void* p) { printf("%d",	*(int32_t*)p); }
};

#endif

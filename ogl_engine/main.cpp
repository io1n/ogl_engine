#include <iostream>

#include "render/vbo.h"
#include "render/mappers/texture_2d_array.h"

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
	vbo<texture_2d_array> a(256);

	uint32_t v;

	for (uint32_t i = 0; i != 0xFFFF; ++i)
		v = texture_2d_array::i.float_per_vert();

	printf("%lu\n", v);

	for (uint32_t i = 0; i != sizeof(texture_2d_array); i += 4)
		printf("%08X\t", *(uint32_t*)((uint8_t*)&texture_2d_array::i + i));

	printf("\n");

	return 0;
}

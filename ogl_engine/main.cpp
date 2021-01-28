#include <iostream>

#include "render/mapped_vbo.h"
#include "render/mappers/texture_2d_array.h"
#include "render/mappers/test_mapper.h"

struct vec3f
{
	float x, y, z;
};

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwHideWindow(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSwapInterval(1);

	mapped_vbo<texture_2d_array> zxc(4096);
	mapped_vbo<test_mapper> qwe(4096);

	qwe.create();
	qwe.create();

	std::vector<base_vbo*> dead_inside;
	dead_inside.push_back(&zxc);
	dead_inside.push_back(&qwe);

	for (auto i : dead_inside)
		i->show();

	using t = texture_2d_array;

	vec3f qwezxc = { 228.f, 1337.f, 1488.f };

	mapped_vbo<t>::vertex* v[4] = {zxc.create(), zxc.create(), zxc.create(), zxc.create()};
	//v[0]->set<float>(0.25f, t::i.POS, X);
	v[0]->set<vec3f>(qwezxc, t::i.POS, Y);
	v[1]->set<uint32_t>(0xDEAD4A11, t::i.COLOR, X, Z);
	v[2]->set<float>(0.75f, t::i.POS, Z);
	v[3]->set<float>(1.f, t::i.POS, W);

	zxc.show();

	glfwDestroyWindow(window);

	glfwTerminate();

	for (uint32_t i = 0; i != sizeof(texture_2d_array); i += sizeof(uint32_t))
		printf("%08X\t", *(uint32_t*)((uint8_t*)&texture_2d_array::i + i));


	return 0;
}

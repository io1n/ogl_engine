#include <iostream>

#include "render/vbo.h"
#include "render/mappers/texture_2d_array.h"

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

	double a, b;

	a = glfwGetTime();

	vbo<texture_2d_array> zxc(8192);

	b = glfwGetTime();

	printf("%f\n", b - a);

	for (uint32_t i = 0; i != sizeof(texture_2d_array) >> 0b10; ++i)
		printf("%08X\t", *((uint32_t*)&texture_2d_array::i + i));

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}

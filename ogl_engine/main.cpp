#include <iostream>

#include "render/VBO.h"

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
	glfwInit();

	printf("%f\n", glfwGetTime());

	glfwTerminate();

	return 0;
}
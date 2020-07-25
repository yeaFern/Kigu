#pragma once

#include <GLFW/glfw3.h>

namespace Kigu
{
    class OpenGLContext
    {
    public:
		void PreInit();
		void Init(GLFWwindow* window);

		void Swap(GLFWwindow* window);

		void Destroy();
    };
}

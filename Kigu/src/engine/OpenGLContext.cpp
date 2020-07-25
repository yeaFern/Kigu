#include "engine/OpenGLContext.h"

namespace Kigu
{
	void OpenGLContext::PreInit()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifdef KIGU_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	}

	void OpenGLContext::Init(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
#ifdef KIGU_DEBUG
		// TODO: Set up OpenGL debug handler.
#endif
	}

	void OpenGLContext::Swap(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}

	void OpenGLContext::Destroy()
	{
	}
}

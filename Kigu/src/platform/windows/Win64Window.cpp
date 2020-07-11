#include "Win64Window.h"
#ifdef KIGU_WINDOWS

#include "../opengl/OpenGLContext.h"
#include "../vulkan/VulkanContext.h"

namespace Kigu
{
    Win64Window::Win64Window()
    {
		if (!glfwInit())
		{
			// TODO: Error.
		}

		this->m_Context = new VulkanContext;
		this->m_Context->PreInit(nullptr);

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		this->m_Handle = glfwCreateWindow(1280, 720, "Kigu", nullptr, nullptr);
		if (m_Handle == nullptr)
		{
			// TODO: Error.
		}

		this->m_Context->Init(m_Handle);

		glfwShowWindow(m_Handle);
    }

    Win64Window::~Win64Window()
    {
		glfwTerminate();
    }

	void Win64Window::Update()
	{
		glfwPollEvents();
		m_Context->Swap();
	}
    
    WindowPtr Window::New()
    {
        return std::make_shared<Win64Window>();
    }
}

#endif

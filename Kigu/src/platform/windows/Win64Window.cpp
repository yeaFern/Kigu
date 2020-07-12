#include "Win64Window.h"
#ifdef KIGU_WINDOWS

#ifdef KIGU_OPENGL
#include "../opengl/OpenGLContext.h"
#elif defined(KIGU_VULKAN)
#include "../vulkan/VulkanContext.h"
#endif

namespace Kigu
{
    Win64Window::Win64Window()
    {
		if (!glfwInit())
		{
			// TODO: Error.
		}

#ifdef KIGU_OPENGL
		this->m_Context = new OpenGLContext;
#elif defined(KIGU_VULKAN)
		this->m_Context = new VulkanContext;
#endif

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
		m_Context->Destroy();
		glfwTerminate();
    }

	void Win64Window::Update()
	{
		glfwPollEvents();
		m_Context->Swap();
	}

	bool Win64Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_Handle);
	}
    
    WindowPtr Window::New()
    {
        return std::make_shared<Win64Window>();
    }
}

#endif

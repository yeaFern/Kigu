#include "engine/Window.h"

namespace Kigu
{
    Window::Window(const WindowProperties& properties)
    {
		if (!glfwInit())
		{
			// TODO: Error.
		}

		this->m_Context.PreInit();

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		this->m_Handle = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), nullptr, nullptr);
		if (m_Handle == nullptr)
		{
			// TODO: Error.
		}

		this->m_Context.Init(m_Handle);

		glfwShowWindow(m_Handle);
    }

	Window::~Window()
    {
		m_Context.Destroy();

		glfwTerminate();
    }

	void Window::Update()
	{
		glfwPollEvents();
		m_Context.Swap(m_Handle);
	}

	bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_Handle);
	}
    
    WindowPtr Window::New(const WindowProperties& properties)
    {
        return std::make_unique<Window>(properties);
    }
}

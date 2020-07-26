#include "engine/EngineCore.h"
#include "engine/Window.h"
#include "events/Event.h"

namespace Kigu
{
    Window::Window(const WindowProperties& properties)
    {
		if (!glfwInit())
		{
			LogFatal("Failed to initialize GLFW.");
		}

		this->m_Context.PreInit();

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		this->m_Handle = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), nullptr, nullptr);
		if (m_Handle == nullptr)
		{
			LogFatal("Failed to create window.");
		}

		this->m_Context.Init(m_Handle);
		gladLoadGL();

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window) {
			EngineCore::Instance()->PostEvent<WindowCloseEvent>();
		});

		glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
			EngineCore::Instance()->PostEvent<WindowResizeEvent>(width, height);
		});

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

	int Window::GetWidth() const
	{
		int w;
		glfwGetWindowSize(m_Handle, &w, nullptr);
		return w;
	}

	int Window::GetHeight() const
	{
		int h;
		glfwGetWindowSize(m_Handle, nullptr, &h);
		return h;
	}

	GLFWwindow* Window::GetGLFWWindow() const
	{
		return m_Handle;
	}
    
    WindowPtr Window::New(const WindowProperties& properties)
    {
        return std::make_unique<Window>(properties);
    }
}

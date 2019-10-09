	#include "..\include\Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Window::OnResize(int newWidth, int newHeight)
{
	m_WasResized = true;

	m_Width = newWidth;
	m_Height = newHeight;
}

Window::Window(const std::string& title, EventQueue& eventQueue)
	: m_Width(1280), m_Height(720), m_EventQueue(eventQueue)
{
	if (!glfwInit())
	{
		KIGU_FATAL("Failed to initialize GLFW.");
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		glfwTerminate();
		KIGU_FATAL("Failed to create window.");
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		glfwDestroyWindow(m_Window);
		KIGU_FATAL("Failed to initialize OpenGL.");
	}

	glfwSetWindowUserPointer(m_Window, this);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		((Window*)glfwGetWindowUserPointer(window))->OnResize(width, height);
	});
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	if (m_WasResized)
	{
		m_WasResized = false;
		m_EventQueue.Add<WindowResizeEvent>(m_Width, m_Height);
	}
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

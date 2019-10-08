	#include "..\include\Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(const std::string& title, EventQueue& eventQueue)
	: m_EventQueue(eventQueue)
{
	if (!glfwInit())
	{
		KIGU_FATAL("Failed to initialize GLFW.");
	}

	m_Window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
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

	glfwSetWindowUserPointer(m_Window, &m_EventQueue);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		(*((EventQueue*)glfwGetWindowUserPointer(window))).Add<WindowResizeEvent>(width, height);
	});
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Update() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

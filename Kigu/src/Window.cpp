#include "..\include\Window.h"

#include <GLFW/glfw3.h>

Window::Window(const std::string& title)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << std::endl;
	}

	m_Window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Failed to create window." << std::endl;
	}

	glfwMakeContextCurrent(m_Window);
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

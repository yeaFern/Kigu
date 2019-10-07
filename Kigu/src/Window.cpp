#include "..\include\Window.h"

#include <GLFW/glfw3.h>

void Window::Initialize(const std::string& title)
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

void Window::Update() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();

	m_Window = nullptr;
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

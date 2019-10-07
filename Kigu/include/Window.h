#pragma once

#include <string>
#include <iostream>

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* m_Window;
public:
	Window(const std::string& title);
	~Window();

	void Update() const;

	bool ShouldClose() const;
};

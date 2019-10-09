#pragma once

#include "Event.h"
#include "Error.h"

#include <string>
#include <iostream>

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* m_Window;
	EventQueue& m_EventQueue;

	int m_Width;
	int m_Height;

	bool m_WasResized = false;
	
	void OnResize(int newWidth, int newHeight);
public:
	Window(const std::string& title, EventQueue& eventQueue);
	~Window();

	void Update();

	bool ShouldClose() const;
};

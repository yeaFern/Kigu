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
public:
	Window(const std::string& title, EventQueue& eventQueue);
	~Window();

	void Update() const;

	bool ShouldClose() const;
};

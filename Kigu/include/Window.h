#pragma once

#include <string>
#include <iostream>

struct GLFWwindow;

class Window
{
#pragma region Singleton
public:
	static Window& GetInstance()
	{
		static Window instance;
		return instance;
	}
private:
	Window() {}

public:
	Window(Window const&) = delete;
	void operator=(Window const&) = delete;
#pragma endregion
private:
	GLFWwindow* m_Window;
public:
	void Initialize(const std::string& title);
	void Update() const;

	void Shutdown();

	bool ShouldClose() const;
};

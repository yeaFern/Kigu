#pragma once

#include <string>
#include <memory>

#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

namespace Kigu
{
	struct WindowProperties
	{
		std::string Title = "Kigu";
		uint32_t Width = 1280;
		uint32_t Height = 720;
	
		WindowProperties() = default;
	};

    class Window
    {
	private:
		GLFWwindow* m_Handle;
		OpenGLContext m_Context;
    public:
		Window(const WindowProperties& properties);
		~Window();

		void Update();
		bool IsOpen();
    public:
        static std::unique_ptr<Window> New(const WindowProperties& properties);
    };
    using WindowPtr = std::unique_ptr<Window>;
}

#pragma once

#include "Conditionals.h"
#ifdef KIGU_WINDOWS

#include <GLFW/glfw3.h>

#include <iostream>

#include "engine/Window.h"
#include "engine/GraphicsContext.h"

namespace Kigu
{
    class Win64Window : public Window
    {
	private:
		GLFWwindow* m_Handle;
		GraphicsContext* m_Context;
    public:
        Win64Window();
        virtual ~Win64Window();

		void Update() override;
    };
}

#endif

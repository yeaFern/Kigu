#pragma once

#include "Conditionals.h"
#ifdef KIGU_WINDOWS

#include <GLFW/glfw3.h>

#include "engine/GraphicsContext.h"

namespace Kigu
{
    class OpenGLContext : public GraphicsContext
    {
    private:
		GLFWwindow* m_Window = nullptr;
    public:
		void PreInit(void* data) override;
		void Init(void* data) override;

		void Swap() override;

		void Destroy() override;
    };
}

#endif

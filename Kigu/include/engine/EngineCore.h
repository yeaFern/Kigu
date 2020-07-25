#pragma once

#include "Application.h"
#include "Window.h"

namespace Kigu
{
	class EngineCore
	{
	private:
		Application* m_Application;

		WindowPtr m_Window;

		bool m_Running = false;
	public:
		EngineCore(Application* app);
	private:
		void Initialize();
		void Loop();
	};
}

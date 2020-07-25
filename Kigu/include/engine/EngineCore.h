#pragma once

#include "Application.h"
#include "Window.h"

#include "events/Event.h"
#include "util/Log.h"

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

		void PostEvent(Event& event);
	private:
		void Initialize();
		void Loop();
	public:
		static EngineCore* Instance() { return s_Instance; }
	private:
		static EngineCore* s_Instance;
	};
}

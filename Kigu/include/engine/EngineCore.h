#pragma once

#include <queue>
#include <memory>

#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"

#include "assets/AssetManager.h"
#include "events/Event.h"
#include "util/Log.h"

namespace Kigu
{
	class EngineCore
	{
	private:
		Application* m_Application;

		WindowPtr m_Window;
		ImGuiLayer m_ImGui;

		bool m_Running = false;

		std::queue<std::unique_ptr<Event>> m_EventQueue;
	public:
		EngineCore(Application* app);

		template<typename T, class... Args>
		void PostEvent(Args&&... args);

		Window& GetWindow() { return *m_Window; }
	private:
		void Initialize();
		void Destroy();
		void Loop();
	public:
		static EngineCore* Instance() { return s_Instance; }
	private:
		static EngineCore* s_Instance;
	};

	template<typename T, class ...Args>
	inline void EngineCore::PostEvent(Args&&... args)
	{
		m_EventQueue.push(std::make_unique<T>(std::forward<Args>(args)...));
	}
}

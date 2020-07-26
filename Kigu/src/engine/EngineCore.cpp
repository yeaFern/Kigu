#include "engine/EngineCore.h"
#include "imgui/imgui.h"

namespace Kigu
{
	EngineCore* EngineCore::s_Instance = nullptr;

	EngineCore::EngineCore(Application* app)
		: m_Application(app)
	{
		if (s_Instance != nullptr)
		{
			LogFatal("Application already created.");
		}

		EngineCore::s_Instance = this;
		Initialize();
		Loop();
		Destroy();
	}

	void EngineCore::Initialize()
	{
		WindowProperties properties;
		this->m_Window = Window::New(properties);

		this->m_ImGui.Initialize();

		this->m_Application->OnInitialize();
		this->m_Running = true;
	}

	void EngineCore::Destroy()
	{
		this->m_ImGui.Destroy();
	}

	void EngineCore::Loop()
	{
		while (m_Running)
		{
			while (!m_EventQueue.empty())
			{
				auto& event = *m_EventQueue.front();
				
				if (event.Type == EventType::WindowClose)
				{
					auto& e = static_cast<WindowCloseEvent&>(event);
					m_Running = false;
				}

				if (event.Type == EventType::WindowResize)
				{
					auto& e = static_cast<WindowResizeEvent&>(event);
					LogInfo(e.Width << "x" << e.Height);

					// TODO: Move to renderer or something.
					glViewport(0, 0, e.Width, e.Height);
				}

				m_EventQueue.pop();
			}

			this->m_Application->OnUpdate();

			this->m_ImGui.Begin();
			ImGui::ShowDemoWindow();
			this->m_ImGui.End();

			this->m_Window->Update();
		}
	}
}

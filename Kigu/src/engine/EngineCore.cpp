#pragma once

#include "engine/EngineCore.h"

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
	}

	void EngineCore::Initialize()
	{
		WindowProperties properties;
		this->m_Window = Window::New(properties);

		this->m_Application->OnInitialize();
		this->m_Running = true;
	}

	void EngineCore::Loop()
	{
		while (m_Running)
		{
			this->m_Application->OnUpdate();

			this->m_Window->Update();
		}
	}
}

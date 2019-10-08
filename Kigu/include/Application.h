#pragma once

#include "Window.h"
#include "Scene.h"
#include "Event.h"

#include <string>

// TODO: Temporary.
#include <glad/glad.h>

struct Settings
{
	std::string name = "Kigu";
};

class Application
{
private:
	Window m_Window;
	SceneManager m_SceneManager;

	EventQueue m_EventQueue;

	bool m_Running = true;
public:
	Application(const Settings& settings)
		: m_Window(settings.name, m_EventQueue)
	{
	}

	inline SceneManager& GetSceneManager()
	{
		return m_SceneManager;
	}

	inline EventQueue& GetEventQueue()
	{
		return m_EventQueue;
	}

	inline Window& GetWindow()
	{
		return m_Window;
	}

	inline void Terminate()
	{
		m_Running = false;
	}

	inline bool IsRunning() const
	{
		return m_Running;
	}
};

namespace Kigu
{
	template<class T>
	void Start(const Settings& settings = {})
	{
		static_assert(std::is_base_of<Scene, T>::value);
		
		Application app(settings);

		// 1. Initialize core systems.
		//    - GLFW
		//    - OpenGL
		//    - OpenAL

		// 2. Do Kigu initialization.
		//    - Load shaders.
		//    - Initialize renderers.
		//    - Show window.
		//    - Display loading screen.
		//    - Load application asset manifest.
		//    - Initialize application.
		//    - etc

		app.GetSceneManager().PushScene<T>();

		// TODO: Proper engine loop.
		while (app.IsRunning())
		{
			app.GetEventQueue().Process([](const Event& e) {
				std::cout << "Processing event." << std::endl;
			});

			app.GetSceneManager().OnUpdate(app);

			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, 0.5f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(-0.5f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(0.5f, -0.5f);
			glEnd();

			app.GetWindow().Update();
			if (app.GetWindow().ShouldClose())
			{
				app.Terminate();
			}
		}
	}
}

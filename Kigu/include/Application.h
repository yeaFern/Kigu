#pragma once

#include "Scene.h"

#include <string>

struct Settings
{
	std::string name = "Kigu";
};

class Application
{
private:
	SceneManager m_SceneManager;
	bool m_Running = true;
public:
	inline SceneManager& GetSceneManager()
	{
		return m_SceneManager;
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
		
		Application app;
		app.GetSceneManager().PushScene<T>();

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

		// TODO: Proper engine loop.
		while (app.IsRunning())
		{
			app.GetSceneManager().OnUpdate(app);
		}
	}
}

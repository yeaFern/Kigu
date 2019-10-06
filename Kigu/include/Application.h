#pragma once

#include "LoadingManager.h"

#include <string>

struct Settings
{
	std::string name = "Kigu";
};

class Application
{
private:

public:
	virtual void OnLoad(LoadingManager& manager) = 0;
};

namespace Kigu
{
	template<class T>
	void Start(const Settings& settings = {})
	{
		static_assert(std::is_base_of<Application, T>::value);
		T app;

		// 1. Initialize core systems.
		//    - GLFW
		//    - OpenGL
		//    - OpenAL

		LoadingManager manager;
		// 2. Do Kigu initialization.
		//    - Load shaders.
		//    - Initialize renderers.
		//    - Show window.
		//    - Display loading screen.
		//    - Initialize application.
		app.OnLoad(manager);
		//    - Load assets.
		//    - etc
	}
}

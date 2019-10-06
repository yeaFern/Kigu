#pragma once

#include <string>

struct Settings
{
	std::string name = "Kigu";
};

class Application
{
private:

public:

};

namespace Kigu
{
	template<class T>
	void Start(const Settings& settings = {})
	{
		static_assert(std::is_base_of<Application, T>::value);
		T* app = new T;

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
	}
}

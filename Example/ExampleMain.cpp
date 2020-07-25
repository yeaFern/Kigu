#include <Kigu.h>
#include <KiguMain.h>

#include <iostream>

class ExampleApplication : public Kigu::Application
{
public:
	void OnInitialize()
	{
		Kigu::ShaderPtr shader = Kigu::Shader::Create(
			"Basic",
			Kigu::File("Data/Shaders/Basic.vs"),
			Kigu::File("Data/Shaders/Basic.fs")
		);
	}

	void OnUpdate()
	{
	}
};

namespace Kigu
{
	Application* Create()
	{
		return new ExampleApplication;
	}
}

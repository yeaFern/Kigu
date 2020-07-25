#include <Kigu.h>
#include <KiguMain.h>

#include <iostream>

class ExampleApplication : public Kigu::Application
{
public:
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

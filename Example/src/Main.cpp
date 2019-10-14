#include <Kigu.h>

#include <iostream>

struct MyComponent
{
	std::string name;
};

class MainScene : public Scene
{
public:
	void OnEnter() override
	{
		auto e = AddEntity();
		e.Add<MyComponent>("Kigu_Object");
		e.Add<Transform>(0.5f, 5.2f);
	}
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MainScene>(settings);

	return 0;
}

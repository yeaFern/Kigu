#include <Kigu.h>

#include <iostream>

struct MyComponent
{
	std::string name;
};

MakePrefab(BaseObject)
	AddComponent(Transform, 1.5f, 5.0f)
	AddComponent(MyComponent, "Kigu_Object")
DonePrefab()

class MainScene : public Scene
{
public:
	void OnEnter() override
	{
		auto e = AddEntity(BaseObject);
	}
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MainScene>(settings);

	return 0;
}

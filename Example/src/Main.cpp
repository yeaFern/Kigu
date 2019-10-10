#include <Kigu.h>

#include <iostream>

class MainScene : public Scene
{
public:
	void OnEnter() override
	{
		std::cout << "Adding game objects" << std::endl;
	}
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MainScene>(settings);

	return 0;
}

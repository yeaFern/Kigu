#include <Kigu.h>

#include <iostream>

class MyApplication : Application
{
public:
	void OnLoad(LoadingManager& manager) override
	{
		std::cout << "Loading!" << std::endl;
		// manager.LoadAsset("sprite.png");
	}
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MyApplication>(settings);

	return 0;
}

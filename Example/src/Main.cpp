#include <Kigu.h>

#include <iostream>

class MainScene : public Scene
{
public:
	void OnUpdate(Application& app) override
	{
		std::cout << "Update" << std::endl;

		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);

		if (input == "quit")
		{
			app.Terminate();
		}
	}
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MainScene>(settings);

	return 0;
}

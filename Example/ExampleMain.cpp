#include <Kigu.h>
#include <iostream>

int main(int argc, char** argv)
{
	auto window = Kigu::Window::New({});

	while (window->IsOpen())
	{
		window->Update();
	}

    return 0;
}

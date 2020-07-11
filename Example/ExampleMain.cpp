#include <Kigu.h>
#include <iostream>

int main(int argc, char** argv)
{
    auto window = Kigu::Window::New();

	for (;;)
	{
		window->Update();
	}

    return 0;
}

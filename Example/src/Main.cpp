#include <Kigu.h>

#include <iostream>

class MyApplication : Application
{
public:
	
};

int main(int argc, char** argv)
{
	Settings settings;

	Kigu::Start<MyApplication>(settings);

	return 0;
}

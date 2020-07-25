#pragma once

#include "engine/Application.h"
#include "engine/EngineCore.h"

namespace Kigu
{
	extern Application* Create();
}

int main(int argc, char** argv)
{
	auto application = Kigu::Create();

	Kigu::EngineCore engine(application);

	delete application;

	return 0;
}

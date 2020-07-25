#pragma once

namespace Kigu
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void OnUpdate() = 0;
	};
}

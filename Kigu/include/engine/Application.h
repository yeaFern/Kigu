#pragma once

namespace Kigu
{
	class Application
	{
	public:
		virtual ~Application() = default;

		virtual void OnInitialize() = 0;

		virtual void OnUpdate() = 0;
	};
}

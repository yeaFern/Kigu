#pragma once

#include <memory>

namespace Kigu
{
    class GraphicsContext
    {
    public:
		virtual void PreInit(void* data) = 0;
		virtual void Init(void* data) = 0;

		virtual void Swap() = 0;
    };
}

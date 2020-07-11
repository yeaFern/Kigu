#pragma once

#include "Conditionals.h"
#ifdef KIGU_WINDOWS

#include "engine/GraphicsContext.h"

namespace Kigu
{
    class VulkanContext : public GraphicsContext
    {
    public:
		void PreInit(void* data) override;
		void Init(void* data) override;

		void Swap() override;
    };
}

#endif

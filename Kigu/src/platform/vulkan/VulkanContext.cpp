#include "VulkanContext.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

namespace Kigu
{
	void VulkanContext::PreInit(void* data)
	{
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#ifdef KIGU_DEBUG
#endif
	}

	void VulkanContext::Init(void* data)
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::cout << "found " << extensionCount << " supported extensions" << std::endl;
#ifdef KIGU_DEBUG
#endif
	}

	void VulkanContext::Swap()
	{
	}
}

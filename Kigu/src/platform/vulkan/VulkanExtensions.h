#pragma once

#include "Conditionals.h"
#if defined(KIGU_WINDOWS) && defined(KIGU_VULKAN)

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Kigu
{
	VkResult CreateDebugUtilsMessengerEXT(
		VkInstance,
		const VkDebugUtilsMessengerCreateInfoEXT*,
		const VkAllocationCallbacks*,
		VkDebugUtilsMessengerEXT*
	);

	void DestroyDebugUtilsMessengerEXT(
		VkInstance,
		VkDebugUtilsMessengerEXT,
		const VkAllocationCallbacks*
	);
}

#endif

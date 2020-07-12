#include "VulkanContext.h"
#include "VulkanExtensions.h"

namespace Kigu
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData
	)
	{
		std::cerr << "validation layer: " << callbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType =VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = VulkanDebugCallback;
		createInfo.pUserData = nullptr;
	}

	struct QueueFamilyInfo
	{
		std::optional<uint32_t> GraphicsFamily;
		std::optional<uint32_t> PresentFamily;

		bool IsComplete() const
		{
			return GraphicsFamily.has_value() && PresentFamily.has_value();
		}
	};

	struct SwapchainDetails
	{
		VkSurfaceCapabilitiesKHR Capabilities;
		std::vector<VkSurfaceFormatKHR> Formats;
		std::vector<VkPresentModeKHR> PresentModes;
	};

	static QueueFamilyInfo GetQueueInfo(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		QueueFamilyInfo availableQueues;
		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				availableQueues.GraphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport)
			{
				availableQueues.PresentFamily = i;
			}

			i++;
		}

		return availableQueues;
	}

	static SwapchainDetails GetSwapchainDetails(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		SwapchainDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.Capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
		if (formatCount != 0)
		{
			details.Formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.Formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
		if (presentModeCount != 0)
		{
			details.PresentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.PresentModes.data());
		}

		return details;
	}

	static VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
	{
		for (const auto& format : formats) {
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return format;
			}
		}

		return formats[0];
	}

	static VkPresentModeKHR ChooseSwapchainPresentMode(const std::vector<VkPresentModeKHR>& modes)
	{
		for (const auto& mode : modes)
		{
			if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return mode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	static VkExtent2D ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			VkExtent2D actualExtent = { 1280, 720 };

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	void VulkanContext::PreInit(void* data)
	{
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	void VulkanContext::Init(void* data)
	{
		CreateInstance();

		if (EnableDebugFeatures)
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo = { };
			PopulateDebugMessengerCreateInfo(createInfo);

			if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
			{
				// TODO: Error.
			}
		}

		if (glfwCreateWindowSurface(m_Instance, (GLFWwindow*)data, nullptr, &m_Surface) != VK_SUCCESS)
		{
			// TODO: Error.
		}

		FindPhysicalDevice();
		FindLogicalDevice();
		CreateSwapchain();
	}

	void VulkanContext::Swap()
	{
	}

	void VulkanContext::Destroy()
	{
		for (auto view : m_SwapchainImageViews)
		{
			vkDestroyImageView(m_Device, view, nullptr);
		}

		vkDestroySwapchainKHR(m_Device, m_Swapchain, nullptr);
		vkDestroyDevice(m_Device, nullptr);

		if (EnableDebugFeatures)
		{
			DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
		}

		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanContext::CreateInstance()
	{
		VkApplicationInfo appInfo = { };
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Kigu Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.pEngineName = "Kigu";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = { };
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.pNext = nullptr;

		auto extensions = GetRequiredExtensions();
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		if (EnableDebugFeatures)
		{
			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { };
			if (CheckValidationLayers())
			{
				createInfo.enabledLayerCount = VulkanValidationLayers.size();
				createInfo.ppEnabledLayerNames = VulkanValidationLayers.data();

				PopulateDebugMessengerCreateInfo(debugCreateInfo);
				createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
			}
			else
			{
				// TODO: Error.
			}
		}

		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
		{
			// TODO: Error.
		}
	}

	void VulkanContext::FindPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			// TODO: Error. No GPUs with Vulkan support.
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

		auto CheckDeviceExtensions = [&](VkPhysicalDevice device) -> bool
		{
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> availableExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

			std::set<std::string> requiredExtensions(VulkanDeviceExtensions.begin(), VulkanDeviceExtensions.end());

			for (const auto& extension : availableExtensions)
			{
				requiredExtensions.erase(extension.extensionName);
			}

			return requiredExtensions.empty();
		};

		auto CheckDevice = [&](VkPhysicalDevice device) -> bool
		{
			VkPhysicalDeviceProperties deviceProperties;
			VkPhysicalDeviceFeatures deviceFeatures;

			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

			bool extensionSupport = CheckDeviceExtensions(device);
			QueueFamilyInfo availableQueues = GetQueueInfo(device, m_Surface);

			bool swapchainSupport = false;
			if (extensionSupport)
			{
				SwapchainDetails details = GetSwapchainDetails(device, m_Surface);
				swapchainSupport = !details.Formats.empty() && !details.PresentModes.empty();
			}

			return availableQueues.IsComplete() && extensionSupport && swapchainSupport;
		};

		for (const auto& device : devices)
		{
			if (CheckDevice(device))
			{
				m_PhysicalDevice = device;
				break;
			}
		}

		if (m_PhysicalDevice == nullptr)
		{
			// TODO: Error.
		}
	}

	void VulkanContext::FindLogicalDevice()
	{
		QueueFamilyInfo availableQueues = GetQueueInfo(m_PhysicalDevice, m_Surface);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> queueFamilies = {
			availableQueues.GraphicsFamily.value(),
			availableQueues.PresentFamily.value()
		};

		float priority = 1.0f;
		for (uint32_t family : queueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = { };
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = family;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &priority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures = { };

		VkDeviceCreateInfo createInfo = { };
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = queueCreateInfos.size();
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = VulkanDeviceExtensions.size();
		createInfo.ppEnabledExtensionNames = VulkanDeviceExtensions.data();
		if (EnableDebugFeatures)
		{
			createInfo.enabledLayerCount = VulkanValidationLayers.size();
			createInfo.ppEnabledLayerNames = VulkanValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
		{
			// TODO: Error.
		}

		vkGetDeviceQueue(m_Device, availableQueues.GraphicsFamily.value(), 0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_Device, availableQueues.PresentFamily.value(), 0, &m_PresentQueue);
	}

	void VulkanContext::CreateSwapchain()
	{
		SwapchainDetails details = GetSwapchainDetails(m_PhysicalDevice, m_Surface);
		VkSurfaceFormatKHR format = ChooseSwapchainSurfaceFormat(details.Formats);
		VkPresentModeKHR presentMode = ChooseSwapchainPresentMode(details.PresentModes);
		VkExtent2D extent = ChooseSwapchainExtent(details.Capabilities);

		uint32_t imageCount = details.Capabilities.minImageCount + 1;
		if (details.Capabilities.maxImageCount > 0 && imageCount > details.Capabilities.maxImageCount)
		{
			imageCount = details.Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = { };
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_Surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = format.format;
		createInfo.imageColorSpace = format.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyInfo indices = GetQueueInfo(m_PhysicalDevice, m_Surface);
		uint32_t queueFamilyIndices[] = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

		if (indices.GraphicsFamily != indices.PresentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = details.Capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS)
		{
			// TODO: Error.
		}

		{
			uint32_t imageCount = 0;
			vkGetSwapchainImagesKHR(m_Device, m_Swapchain, &imageCount, nullptr);
			m_SwapchainImages.resize(imageCount);
			vkGetSwapchainImagesKHR(m_Device, m_Swapchain, &imageCount, m_SwapchainImages.data());
		}

		m_SwapchainFormat = format.format;
		m_SwapchainExtent = extent;

		m_SwapchainImageViews.resize(m_SwapchainImages.size());
		for (int i = 0; i < m_SwapchainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo = { };
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_SwapchainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_SwapchainFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_Device, &createInfo, nullptr, &m_SwapchainImageViews[i]) != VK_SUCCESS)
			{
				// TODO: Error.
			}
		}
	}

	std::vector<const char*> VulkanContext::GetRequiredExtensions() const
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (EnableDebugFeatures)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	bool VulkanContext::CheckValidationLayers() const
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const auto& requested : VulkanValidationLayers)
		{
			bool found = false;

			for (const auto& properties : availableLayers)
			{
				if (strcmp(requested, properties.layerName) == 0)
				{
					found = true;
				}
			}

			if (!found)
			{
				return false;
			}
		}

		return true;
	}
}

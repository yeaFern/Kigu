#pragma once

#include "Conditionals.h"
#ifdef KIGU_WINDOWS

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <set>
#include <cstdint>

#include "engine/GraphicsContext.h"

namespace Kigu
{
	static const std::array<const char*, 1> VulkanValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	static const std::array<const char*, 1> VulkanDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

    class VulkanContext : public GraphicsContext
    {
	private:
#ifdef KIGU_DEBUG
		static constexpr bool EnableDebugFeatures = true;
#else
		static constexpr bool EnableDebugFeatures = false;
#endif
	private:
		VkInstance m_Instance = nullptr;
		VkSurfaceKHR m_Surface;
		VkPhysicalDevice m_PhysicalDevice = nullptr;
		VkDevice m_Device = nullptr;

		VkSwapchainKHR m_Swapchain = nullptr;
		VkFormat m_SwapchainFormat;
		VkExtent2D m_SwapchainExtent;
		std::vector<VkImage> m_SwapchainImages;
		std::vector<VkImageView> m_SwapchainImageViews;

		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		VkDebugUtilsMessengerEXT m_DebugMessenger = nullptr;
    public:
		void PreInit(void* data) override;
		void Init(void* data) override;

		void Swap() override;

		void Destroy() override;
	private:
		void CreateInstance();
		void FindPhysicalDevice();
		void FindLogicalDevice();
		void CreateSwapchain();

		std::vector<const char*> GetRequiredExtensions() const;
		bool CheckValidationLayers() const;
    };
}

#endif

// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/VulkanWrapper/PhysicalDevice.hpp>

namespace VkTests {
    PhysicalDevice::PhysicalDevice(Instance& instance, const VkPhysicalDevice physicalDevice)
        : m_Instance{instance}, m_Handle{physicalDevice} {
        vkGetPhysicalDeviceFeatures(physicalDevice, &m_Features);
        vkGetPhysicalDeviceProperties(physicalDevice, &m_Properties);
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &m_MemoryProperties);

        Log::Trace("Found GPU: {}", m_Properties.deviceName);

        UInt32 queueFamilyPropertiesCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertiesCount, nullptr);
        m_QueueFamilyProperties = std::vector<VkQueueFamilyProperties>(queueFamilyPropertiesCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertiesCount,
                                                 m_QueueFamilyProperties.data());

        UInt32 deviceExtensionCount;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionCount, nullptr);
        m_Extensions = std::vector<VkExtensionProperties>(deviceExtensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionCount, m_Extensions.data());

        // Display supported extensions
        if (!m_Extensions.empty()) {
            Log::Debug("Device supports the following extensions:");
            for (auto& extension : m_Extensions) {
                Log::Debug("\t- {}", extension.extensionName);
            }
        }
    }

}

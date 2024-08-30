// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

#include <VulkanTests/Core/Logger.hpp>

#include <VulkanTests/Renderer/Error.hpp>

namespace VkTests {
    inline Instance& PhysicalDevice::GetInstance() const {
        return m_Instance;
    }

    inline VkBool32
    PhysicalDevice::IsPresentSupported(const VkSurfaceKHR surface, const UInt32 queueFamilyIndex) const {
        VkBool32 presentSupported{VK_FALSE};

        if (surface != VK_NULL_HANDLE) {
            VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(m_Handle, queueFamilyIndex, surface, &presentSupported));
        }

        return presentSupported;
    }

    inline bool PhysicalDevice::IsExtensionSupported(const std::string& extension) const {
        return std::ranges::find_if(m_Extensions, [extension](auto& deviceExtension) {
            return std::strcmp(deviceExtension.extensionName, extension.c_str()) == 0;
        }) != m_Extensions.end();
    }

    inline VkFormatProperties PhysicalDevice::GetFormatProperties(const VkFormat format) const {
        VkFormatProperties formatProperties;

        vkGetPhysicalDeviceFormatProperties(m_Handle, format, &formatProperties);

        return formatProperties;
    }

    inline VkPhysicalDevice PhysicalDevice::GetHandle() const {
        return m_Handle;
    }

    inline const VkPhysicalDeviceFeatures& PhysicalDevice::GetFeatures() const {
        return m_Features;
    }

    inline const VkPhysicalDeviceProperties& PhysicalDevice::GetProperties() const {
        return m_Properties;
    }

    inline const VkPhysicalDeviceMemoryProperties& PhysicalDevice::GetMemoryProperties() const {
        return m_MemoryProperties;
    }

    inline const std::vector<VkQueueFamilyProperties> PhysicalDevice::GetQueueFamilyProperties() const {
        return m_QueueFamilyProperties;
    }

    inline UInt32 PhysicalDevice::GetQueueFamilyPerformanceQueryPasses(
        const VkQueryPoolPerformanceCreateInfoKHR* perfQueryCreateInfo) const {
        UInt32 passesNeeded;
        vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(GetHandle(), perfQueryCreateInfo, &passesNeeded);

        return passesNeeded;
    }

    inline void PhysicalDevice::EnumerateQueueFamilyPerformanceQueryCounters(const UInt32 queueFamilyIndex,
                                                                             UInt32* count,
                                                                             VkPerformanceCounterKHR* counters,
                                                                             VkPerformanceCounterDescriptionKHR*
                                                                             descriptions) const {
        VK_CHECK(
            vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(GetHandle(), queueFamilyIndex, count,
                counters, descriptions));
    }

    inline const VkPhysicalDeviceFeatures PhysicalDevice::GetRequestedFeatures() const {
        return m_RequestedFeatures;
    }

    inline VkPhysicalDeviceFeatures& PhysicalDevice::GetMutableRequestedFeatures() {
        return m_RequestedFeatures;
    }

    inline void* PhysicalDevice::GetExtensionFeatureChain() const {
        return m_LastRequestedExtensionFeature;
    }
    
    template <typename T>
    T& PhysicalDevice::RequestExtensionFeatures(VkStructureType type) {
        // We cannot request extension features if the physical device properties 2 instance extension is not enabled.
        if (!m_Instance.IsEnabled(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME)) {
            Log::Fatal({0x02, 0x08}, "Couldn't request feature from device as {} isn't enabled.",
                       VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
        }

        // If the type already exists in the map, return a casted pointer to get the extension feature struct.
        if (const auto extensionFeaturesIt = m_ExtensionFeatures.find(type);
            extensionFeaturesIt != m_ExtensionFeatures.end()) {
            return *static_cast<T*>(extensionFeaturesIt->second.get());
        }

        // Get the extension features
        VkPhysicalDeviceFeatures2KHR physicalDeviceFeatures;
        physicalDeviceFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;

        T extension;
        extension.sType = type;

        physicalDeviceFeatures.pNext = &extension;

        vkGetPhysicalDeviceFeatures2KHR(m_Handle, &physicalDeviceFeatures);

        // Insert the extension feature into the extension features map so its ownership is held.
        m_ExtensionFeatures.insert({type, std::make_shared<T>(extension)});

        // Pull out the dereferenced void pointer, we can assume its type based on the template.
        auto* extensionPtr = static_cast<T*>(m_ExtensionFeatures.find(type)->second.get());

        // If an extension feature has already been requested, we shift the linked list down by one,
        // making this current extension the new base pointer.
        if (m_LastRequestedExtensionFeature) {
            extensionPtr->pNext = m_LastRequestedExtensionFeature;
        }
        m_LastRequestedExtensionFeature = extensionPtr;

        return *extensionPtr;
    }

    inline void PhysicalDevice::SetHighPriorityGraphicsQueueEnable(const bool enable) {
        m_HighPriorityGraphicsQueue = enable;
    }

    inline bool PhysicalDevice::HasHighPriorityGraphicsQueue() const {
        return m_HighPriorityGraphicsQueue;
    }

}

// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VULKANWRAPPER_PHYSICALDEVICE_HPP
#define VK_TESTS_RENDERER_VULKANWRAPPER_PHYSICALDEVICE_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/VulkanWrapper/Instance.hpp>

namespace VkTests {
    /**
     * @brief A wrapper class for VkPhysicalDevice
     *
     * This class is responsible for handling gpu features, properties, and queue families for the device creation.
     */
    class PhysicalDevice {
    public:
        PhysicalDevice(Instance& instance, VkPhysicalDevice physicalDevice);
        ~PhysicalDevice() = default;

        PhysicalDevice(const PhysicalDevice&) = delete;
        PhysicalDevice(PhysicalDevice&&) = delete;

        PhysicalDevice& operator=(const PhysicalDevice&) = delete;
        PhysicalDevice& operator=(PhysicalDevice&&) = delete;

        [[nodiscard]] inline Instance& GetInstance() const;

        VkBool32 IsPresentSupported(VkSurfaceKHR surface, UInt32 queueFamilyIndex) const;

        [[nodiscard]] bool IsExtensionSupported(const std::string& extension) const;

        [[nodiscard]] inline VkFormatProperties GetFormatProperties(VkFormat format) const;

        [[nodiscard]] inline VkPhysicalDevice GetHandle() const;

        [[nodiscard]] inline const VkPhysicalDeviceFeatures& GetFeatures() const;

        [[nodiscard]] inline const VkPhysicalDeviceProperties& GetProperties() const;

        [[nodiscard]] inline const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const;

        [[nodiscard]] inline const std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties() const;

        inline UInt32 GetQueueFamilyPerformanceQueryPasses(
            const VkQueryPoolPerformanceCreateInfoKHR* perfQueryCreateInfo) const;

        void EnumerateQueueFamilyPerformanceQueryCounters(UInt32 queueFamilyIndex, UInt32* count,
                                                          VkPerformanceCounterKHR* counters,
                                                          VkPerformanceCounterDescriptionKHR* descriptions) const;

        [[nodiscard]] inline const VkPhysicalDeviceFeatures GetRequestedFeatures() const;

        inline VkPhysicalDeviceFeatures& GetMutableRequestedFeatures();

        /**
         * @brief Used at logical device creation to pass the extensions feature chain to vkCreateDevice
         * @return A void pointer to the start of the extension linked list.
         */
        [[nodiscard]] inline void* GetExtensionFeatureChain() const;

        /**
        * @brief Requests a third party extension to be used by the engine
        *
        *        To have the features enabled, this function must be called before the logical device
        *        is created. To do this request application specific features inside
        *        Application::RequestGpuFeatures(VkTests::PhysicalDevice& physicalDevice).
        *
        *        If the feature extension requires you to ask for certain features to be enabled, you can
        *        modify the struct returned by this function, it will propagate the changes to the logical
        *        device.
         * @param type The VkStructureType for the requested extension
         * @return The extension feature struct
         */
        template <typename T>
        T& RequestExtensionFeatures(VkStructureType type);

        inline void SetHighPriorityGraphicsQueueEnable(bool enable);

        inline bool HasHighPriorityGraphicsQueue() const;

    private:
        // Handle to the Vulkan instance
        Instance& m_Instance;

        // Handle to the Vulkan physical device
        VkPhysicalDevice m_Handle{VK_NULL_HANDLE};

        // The features that this GPU supports
        VkPhysicalDeviceFeatures m_Features{};

        // The extensions that this GPU supports
        std::vector<VkExtensionProperties> m_Extensions;

        // The GPU properties
        VkPhysicalDeviceProperties m_Properties{};

        // The GPU memory properties
        VkPhysicalDeviceMemoryProperties m_MemoryProperties{};

        // The GPU queue family properties
        std::vector<VkQueueFamilyProperties> m_QueueFamilyProperties;

        // The features that will be requested to be enabled by the logical device
        VkPhysicalDeviceFeatures m_RequestedFeatures{};

        // The last extension feature pointer
        void* m_LastRequestedExtensionFeature{nullptr};

        // Holds the extension features, we use a map to retain an order of requested structures
        std::map<VkStructureType, std::shared_ptr<void>> m_ExtensionFeatures;

        bool m_HighPriorityGraphicsQueue{};
    };
}

#include <VulkanTests/Renderer/VulkanWrapper/PhysicalDevice.inl>

#endif // VK_TESTS_RENDERER_VULKANWRAPPER_PHYSICALDEVICE_HPP

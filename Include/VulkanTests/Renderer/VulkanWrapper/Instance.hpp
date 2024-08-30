// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VULKANWRAPPER_INSTANCE_HPP
#define VK_TESTS_RENDERER_VULKANWRAPPER_INSTANCE_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/VkCommon.hpp>

namespace VkTests {
    class PhysicalDevice;

    /**
     * @brief Returns a list of Khronos/LunarG supported validation layers.
     *        Attempting to enable them in order of preference, starting with later Vulkan SDK versions.
     * @param supportedInstanceLayers A list of validation layers to check against.
     * @return A list of Khronos/LunarG supported validation layers.
     */
    std::vector<const char*> GetOptimalValidationLayers(const std::vector<VkLayerProperties>& supportedInstanceLayers);

    class Instance {
    public:
        enum class APIDebugLevel : UInt8 {
            None = 0,

            Errors = 1,
            Warnings = 2,
            Verbose = 3,
            Debug = 4
        };

        /**
         * @brief Can be set from the GPU selection plugin to explicitly select a GPU instead.
         */
        static std::optional<UInt32> SelectedGpuIndex;

        /**
         * @brief Initializes the Vulkan instance.
         * @param applicationName The name of the application
         * @param debugLevel The debugging level for the debug callback
         * @param requiredExtensions The extensions requested to be enabled
         * @param requiredValidationLayers The validation layers requested to be enabled
         * @param requiredLayerSettings The layer settings to be enabled
         * @param headless Whether the application is requesting a headless setup or not.
         * @param apiVersion The Vulkan API version to use.
         */
        explicit Instance(const std::string& applicationName,
                          APIDebugLevel debugLevel,
                          const std::unordered_map<const char*, bool>& requiredExtensions = {},
                          const std::vector<const char*>& requiredValidationLayers = {},
                          const std::vector<VkLayerSettingEXT>& requiredLayerSettings = {},
                          bool headless = false,
                          UInt32 apiVersion = VK_API_VERSION_1_0);

        /**
         * @brief Queries the GPUs of a VkInstance that is already created
         * @param instance A valid VKInstance
         * @param externallyEnabledExtensions List of extensions that have been enabled, used for following checks e.g. during device creation
         */
        explicit Instance(VkInstance instance,
                          const std::vector<const char*>& externallyEnabledExtensions = {});
        ~Instance();

        Instance(const Instance&) = delete;
        Instance(Instance&&) = delete;

        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) = delete;

        /**
         * @brief Queries the instance for the physical devices available on the machine.
         */
        void QueryGpus();

        /**
         * Tries to find the first available discrete GPU that can render to the given surface.
         * @param surface Surface to test against
         * @return A valid physical device
         */
        PhysicalDevice& GetSuitableGpu(VkSurfaceKHR surface) const;

        /**
         * @brief Tries to find the first available discrete GPU.
         * @return A valid physical device
         */
        PhysicalDevice& GetFirstGpu() const;

        /**
         * @brief Checks if the given extension is enabled in the VkInstance.
         * @param extension An extension to check.
         * @return Whether the extension is enabled or not.
         */
        bool IsEnabled(const char* extension);

        [[nodiscard]] inline VkInstance GetHandle() const;

        inline const std::vector<const char*>& GetExtensions();

    private:
        /**
         * @brief The Vulkan instance
         */
        VkInstance m_Handle{VK_NULL_HANDLE};

        /**
         * @brief The enabled instance extensions.
         */
        std::vector<const char*> m_EnabledExtensions;

#if defined(VK_TESTS_DEBUG) || defined (VK_TESTS_VALIDATION_LAYERS)
        /**
         * @brief Debug utils messenger callback for VK_EXT_debug_utils
         */
        VkDebugUtilsMessengerEXT m_DebugUtilsMessenger{VK_NULL_HANDLE};

        /**
         * @brief The debug report callback
         */
        VkDebugReportCallbackEXT m_DebugReportCallback{VK_NULL_HANDLE};
#endif

        /**
         * @brief The physical devices found on the machine.
         */
        std::vector<std::unique_ptr<PhysicalDevice>> m_Gpus;
    };
}

#include <VulkanTests/Renderer/VulkanWrapper/Instance.inl>

#endif // VK_TESTS_RENDERER_VULKANWRAPPER_INSTANCE_HPP

// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/VulkanWrapper/Instance.hpp>

#include <VulkanTests/Renderer/Error.hpp>
#include <VulkanTests/Renderer/VulkanWrapper/PhysicalDevice.hpp>

#include <VulkanTests/Core/Logger.hpp>

#include <VulkanTests/Utils/Helpers.hpp>

#include <volk.h>

#if defined(VK_TESTS_DEBUG) || defined(VK_TESTS_VALIDATION_LAYERS)
#define USE_VALIDATION_LAYERS
#endif

#if defined(VK_TESTS_VALIDATION_LAYERS) && \
    (defined(VK_TESTS_VALIDATION_LAYERS_GPU_ASSISTED) || \
     defined(VK_TESTS_VALIDATION_LAYERS_BEST_PRACTICES) || \
     defined(VK_TESTS_VALIDATION_LAYERS_SYNCHRONIZATION))
#define USE_VALIDATION_LAYER_FEATURES
#endif

namespace VkTests {
    namespace {
#ifdef USE_VALIDATION_LAYERS
        VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(
            const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            const VkDebugUtilsMessageTypeFlagsEXT messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {
            std::stringstream message;
            message << "Vulkan Log: ";

            // Severity
            if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
                message << "[INFO] ";
            }

            if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                message << "[VERBOSE] ";
            }

            if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                message << "[WARNING] ";
            }

            if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                message << "[ERROR] ";
            }

            // Type
            if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
                message << "[GENERAL] ";
            }

            if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
                message << "[VALIDATION] ";
            }

            if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
                message << "[PERFORMANCE] ";
            }

            message << '[' << pCallbackData->messageIdNumber << ' ';
            if (pCallbackData->pMessageIdName) {
                message << pCallbackData->pMessageIdName;
            }

            message << "]: " << pCallbackData->pMessage;

            if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT ||
                messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                Log::Trace(message.str());
            } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                Log::Warn(message.str());
            } else {
                Log::Error(message.str());
            }

            return VK_FALSE;
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT flags,
                                                            VkDebugReportObjectTypeEXT /*type*/,
                                                            UInt64 /*object*/,
                                                            USize /*location*/,
                                                            Int32 messageCode,
                                                            const char* pLayerPrefix,
                                                            const char* pMessage,
                                                            void* /*pUserData*/) {
            std::stringstream message;
            message << "Vulkan Log: ";

            if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
                message << "[INFO] ";
            }

            if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
                message << "[WARNING] ";
            }

            if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
                message << "[ERROR] ";
            }

            if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
                message << "[PERFORMANCE] ";
            }

            message << "[" << messageCode << "]";
            if (pLayerPrefix) {
                message << "[layer " << pLayerPrefix << "]";
            }

            message << ": " << pMessage;

            if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
                Log::Error(message.str());
            } else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
                Log::Warn(message.str());
            } else {
                Log::Trace(message.str());
            }

            return VK_FALSE; // Don't abort the Vulkan call.
        }
#endif

        bool ValidateLayers(const std::vector<const char*>& required, const std::vector<VkLayerProperties>& available) {
            for (auto layer : required) {
                bool found = false;
                for (auto& availableLayer : available) {
                    if (strcmp(availableLayer.layerName, layer) == 0) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    Log::Error("Validation layer {} not found.", layer);
                    return false;
                }
            }

            return true;
        }
    }

    std::vector<const char*> GetOptimalValidationLayers(const std::vector<VkLayerProperties>& supportedInstanceLayers) {
        std::vector<std::vector<const char*>> validationLayerPriorityList = {
            // The preferred validation layer is "VK_LAYER_KHRONOS_validation"
            {"VK_LAYER_KHRONOS_validation"},

            // Otherwise we use the LunarG meta layer as a fallback
            {"VK_LAYER_LUNARG_standard_validation"},

            // Otherwise we attempt to enable the individual layers that compose the LunarG meta layer since it doesn't exist
            {
                "VK_LAYER_GOOGLE_threading",
                "VK_LAYER_LUNARG_parameter_validation",
                "VK_LAYER_LUNARG_object_tracker",
                "VK_LAYER_LUNARG_core_validation",
                "VK_LAYER_GOOGLE_unique_objects"
            },

            // Otherwise as a last resort we attempt to enable the LunarG core layer as a fallback
            {"VK_LAYER_LUNARG_core_validation"}
        };

        for (auto& validationLayers : validationLayerPriorityList) {
            if (ValidateLayers(validationLayers, supportedInstanceLayers)) {
                return validationLayers;
            }

            Log::Warn("Couldn't enable validation layers (see log for error) - falling back");
        }

        return {};
    }

    std::optional<UInt32> Instance::SelectedGpuIndex;

    namespace {
        bool EnableExtension(const char* requiredExtensionName,
                             const std::vector<VkExtensionProperties>& availableExtensions,
                             std::vector<const char*>& enabledExtensions) {
            for (auto& availableExtension : availableExtensions) {
                if (strcmp(availableExtension.extensionName, requiredExtensionName) == 0) {
                    const auto it = std::ranges::find_if(enabledExtensions,
                                                         [requiredExtensionName](const char* enabledExtensionName) {
                                                             return strcmp(enabledExtensionName, requiredExtensionName)
                                                             == 0;
                                                         });
                    if (it != enabledExtensions.end()) {
                        // Extension is already enabled
                    } else {
                        Log::Trace("Extension {} found, enabling it.", requiredExtensionName);
                        enabledExtensions.emplace_back(requiredExtensionName);
                    }
                    return true;
                }
            }

            Log::Warn("Extension {} not found.", requiredExtensionName);
            return false;
        }

        bool EnableAllExtensions(const std::vector<const char*> requiredExtensionsNames,
                                 const std::vector<VkExtensionProperties>& availableExtensions,
                                 std::vector<const char*>& enabledExtensions) {
            using std::placeholders::_1;

            return std::all_of(requiredExtensionsNames.begin(), requiredExtensionsNames.end(),
                               std::bind(enabledExtensions, _1, availableExtensions, enabledExtensions));
        }
    }

    Instance::Instance(const std::string& applicationName,
                       const APIDebugLevel debugLevel,
                       const std::unordered_map<const char*, bool>& requiredExtensions,
                       const std::vector<const char*>& requiredValidationLayers,
                       const std::vector<VkLayerSettingEXT>& requiredLayerSettings,
                       bool headless,
                       UInt32 apiVersion) {
        UInt32 instanceExtensionCount;
        VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr));

        std::vector<VkExtensionProperties> availableInstanceExtensions(instanceExtensionCount);
        VK_CHECK(
            vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, availableInstanceExtensions.data()
            ));

#ifdef USE_VALIDATION_LAYERS
        // Check if VK_EXT_debug_utils is supported, which supersedes VK_EXT_debug_report
        const bool hasDebugUtils = EnableExtension(
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME, availableInstanceExtensions, m_EnabledExtensions);
        const bool hasDebugReport = EnableExtension(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, availableInstanceExtensions,
                                                    m_EnabledExtensions);

        if (!hasDebugUtils) {
            if (!hasDebugReport) {
                Log::Warn("Neither of {} or {} are available; disabling debug reporting.",
                          VK_EXT_DEBUG_UTILS_EXTENSION_NAME, VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
            }
        }
#endif

#ifdef VK_TESTS_PORTABILITY
        EnableExtension(
            VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, availableInstanceExtensions, m_EnabledExtensions);

        bool portabilityEnumerationAvailable = EnableExtension(
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME, availableInstanceExtensions, m_EnabledExtensions);
#endif

#ifdef USE_VALIDATION_LAYER_FEATURES
        bool validationFeatures = false;
        {
            UInt32 layerInstanceExtensionCount;
            VK_CHECK(vkEnumerateInstanceExtensionProperties("VK_LAYER_KHRONOS_validation", &layerInstanceExtensionCount,
                nullptr));

            std::vector<VkExtensionProperties> availableLayerInstanceExtensions(layerInstanceExtensionCount);
            VK_CHECK(vkEnumerateInstanceExtensionProperties("VK_LAYER_KHRONOS_validation", &layerInstanceExtensionCount,
                availableLayerInstanceExtensions.data()));

            for (const auto& availableExtension : availableLayerInstanceExtensions) {
                if (strcmp(availableExtension.extensionName, VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME) == 0) {
                    validationFeatures = true;
                    Log::Trace("{} is available, enabling it.", VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
                    m_EnabledExtensions.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
                    break;
                }
            }
        }
#endif

        // Try to enable headless surface extension if it exists
        if (headless) {
            const bool hasHeadlessSurface = EnableExtension(
                VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, availableInstanceExtensions, m_EnabledExtensions);

            if (!hasHeadlessSurface) {
                Log::Warn("{} is not available; disabling swapchain creation.", VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
            }
        } else {
            m_EnabledExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        }

        // VK_KHR_get_physical_device_properties2 is a prerequisite of VK_KHR_performance_query
        // which will be used for stats gathering where available.
        EnableExtension(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, availableInstanceExtensions,
                        m_EnabledExtensions);

        auto extensionError = false;
        for (const auto extension : requiredExtensions) {
            auto extensionName = extension.first;
            const auto extensionIsOptional = extension.second;
            if (!EnableExtension(extensionName, availableInstanceExtensions, m_EnabledExtensions)) {
                if (extensionIsOptional) {
                    Log::Warn("Optional instance extension {} not available, some features may be disabled.",
                              extensionName);
                } else {
                    Log::Error("Required instance extension {} not available, cannot run.", extensionName);
                    extensionError = true;
                }
                extensionError = extensionError || !extensionIsOptional;
            }
        }

        if (extensionError) {
            Log::Fatal({0x00, 0x04}, "Required instance extensions are missing.");
        }

        UInt32 instanceLayerCount = 0;
        VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr));

        std::vector<VkLayerProperties> supportedLayers(instanceLayerCount);
        VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, supportedLayers.data()));

        std::vector<const char*> requestedValidationLayers(requiredValidationLayers);

#ifdef USE_VALIDATION_LAYERS
        // Determine the optimal validation layers to enable that are necessary for useful debugging
        std::vector<const char*> optimalValidationLayers = GetOptimalValidationLayers(supportedLayers);
        requestedValidationLayers.insert(requestedValidationLayers.end(), optimalValidationLayers.begin(),
                                         optimalValidationLayers.end());
#endif

        if (ValidateLayers(requestedValidationLayers, supportedLayers)) {
            Log::Trace("Enabled Validation Layers:");
            for (const auto& layer : requestedValidationLayers) {
                Log::Trace("\t- {}", layer);
            }
        } else {
            Log::Fatal({0x02, 0x05}, "Required validation layers are missing.");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = applicationName.c_str();
        appInfo.applicationVersion = 0;
        appInfo.pEngineName = "Vulkan Tests";
        appInfo.engineVersion = 0;
        appInfo.apiVersion = apiVersion;

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        instanceCreateInfo.pApplicationInfo = &appInfo;

        instanceCreateInfo.enabledExtensionCount = ToUInt32(m_EnabledExtensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = m_EnabledExtensions.data();

        instanceCreateInfo.enabledLayerCount = ToUInt32(requestedValidationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = requestedValidationLayers.data();

#ifdef USE_VALIDATION_LAYERS
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo;
        VkDebugReportCallbackCreateInfoEXT debugReportCreateInfo;

        if (hasDebugUtils) {
            debugUtilsCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

            VkDebugUtilsMessageSeverityFlagsEXT messageSeverity = 0;

            if (debugLevel >= APIDebugLevel::Errors) {
                messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            }

            if (debugLevel >= APIDebugLevel::Warnings) {
                messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
            }

            if (debugLevel >= APIDebugLevel::Verbose) {
                messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
            }

            if (debugLevel >= APIDebugLevel::Debug) {
                messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
            }

            debugUtilsCreateInfo.messageSeverity = messageSeverity;
            debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            debugUtilsCreateInfo.pfnUserCallback = DebugUtilsMessengerCallback;

            instanceCreateInfo.pNext = &debugUtilsCreateInfo;
        } else if (hasDebugUtils) {
            debugReportCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
            debugReportCreateInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT |
            VK_DEBUG_REPORT_ERROR_BIT_EXT |
            VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
            debugReportCreateInfo.pfnCallback = DebugCallback;

            instanceCreateInfo.pNext = &debugReportCreateInfo;
        }
#endif

#ifdef VK_TESTS_PORTABILITY
        if (portabilityEnumerationAvailable) {
            instanceCreateInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
#endif

        // Some of the specialized layers need to be enabled explicitly
#ifdef USE_VALIDATION_LAYER_FEATURES
        VkValidationFeaturesEXT validationFeaturesInfo;
        validationFeaturesInfo.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;

        std::vector<VkValidationFeatureEnableEXT> enableFeatures{};
        if (validationFeatures) {
#ifdef VK_TESTS_VALIDATION_LAYERS_GPU_ASSISTED
            enableFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT);
            enableFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT);
#endif
#ifdef VK_TESTS_VALIDATION_LAYERS_BEST_PRACTICES
            enableFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
#endif
#ifdef VK_TESTS_VALIDATION_LAYERS_SYNCHRONIZATION
            enableFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT);
#endif
            validationFeaturesInfo.enabledValidationFeatureCount = ToUInt32(enableFeatures.size());
            validationFeaturesInfo.pEnabledValidationFeatures = enableFeatures.data();
            validationFeaturesInfo.pNext = instanceCreateInfo.pNext;
            instanceCreateInfo.pNext = &validationFeaturesInfo;
        }
#endif

        VkLayerSettingsCreateInfoEXT layerSettingsCreateInfo{};
        layerSettingsCreateInfo.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT;

        // If the layer settings extension is enabled by the application, then activate the layer settings
        // during instance creation.
        if (std::ranges::find(m_EnabledExtensions, VK_EXT_LAYER_SETTINGS_EXTENSION_NAME) != m_EnabledExtensions.end()) {
            layerSettingsCreateInfo.settingCount = ToUInt32(requiredLayerSettings.size());
            layerSettingsCreateInfo.pSettings = requiredLayerSettings.data();
            layerSettingsCreateInfo.pNext = instanceCreateInfo.pNext;
            instanceCreateInfo.pNext = &layerSettingsCreateInfo;
        }

        // Create the Vulkan instance
        VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_Handle);

        if (result != VK_SUCCESS) {
            throw VulkanException(result, "Could not create vulkan instance.");
        }

        volkLoadInstance(m_Handle);

#ifdef USE_VALIDATION_LAYERS
        if (hasDebugUtils) {
            result = vkCreateDebugUtilsMessengerEXT(m_Handle, &debugUtilsCreateInfo, nullptr, &m_DebugUtilsMessenger);
            if (result != VK_SUCCESS) {
                throw VulkanException(result, "Could not create debug utils messenger.");
            }
        } else if (hasDebugReport) {
            result = vkCreateDebugReportCallbackEXT(m_Handle, &debugReportCreateInfo, nullptr, &m_DebugReportCallback);
            if (result != VK_SUCCESS) {
                throw VulkanException(result, "Could not create debug report callback.");
            }
        }
#endif

        QueryGpus();
    }

    Instance::Instance(const VkInstance instance, const std::vector<const char*>& externallyEnabledExtensions)
        : m_Handle(instance) {
        // Some parts of the engine will check for certain extensions to be enabled.
        // To make those work we need to copy over externally enabled extensions into this class
        for (auto extension : externallyEnabledExtensions) {
            m_EnabledExtensions.push_back(extension);
        }

        if (m_Handle != VK_NULL_HANDLE) {
            QueryGpus();
        } else {
            Log::Fatal({0x00, 0x06}, "Vulkan instance is invalid.");
        }
    }

    Instance::~Instance() {
#ifdef USE_VALIDATION_LAYERS
        if (m_DebugUtilsMessenger != VK_NULL_HANDLE) {
            vkDestroyDebugUtilsMessengerEXT(m_Handle, m_DebugUtilsMessenger, nullptr);
        }

        if (m_DebugReportCallback != VK_NULL_HANDLE) {
            vkDestroyDebugReportCallbackEXT(m_Handle, m_DebugReportCallback, nullptr);
        }
#endif

        if (m_Handle != VK_NULL_HANDLE) {
            vkDestroyInstance(m_Handle, nullptr);
        }
    }

    void Instance::QueryGpus() {
        // Querying valid physical devices on the machine
        UInt32 physicalDeviceCount{0};
        VK_CHECK(vkEnumeratePhysicalDevices(m_Handle, &physicalDeviceCount, nullptr));

        if (physicalDeviceCount < 1) {
            Log::Fatal({0x02, 0x07}, "Couldn't find a physical device that supports Vulkan.");
        }

        std::vector<VkPhysicalDevice> physicalDevices;
        physicalDevices.resize(physicalDeviceCount);
        VK_CHECK(vkEnumeratePhysicalDevices(m_Handle, &physicalDeviceCount, physicalDevices.data()));

        // Create GPUs wrapper objects for the VkPhysicalDevice's
        for (auto& physicalDevice : physicalDevices) {
            m_Gpus.push_back(std::make_unique<PhysicalDevice>(*this, physicalDevice));
        }
    }

    PhysicalDevice& Instance::GetSuitableGpu(const VkSurfaceKHR surface) const {
        assert(!m_Gpus.empty() && "No physical devices were found on the system.");

        // A GPU can be explicitly selected via the command line (see the GPU selection plugin),
        // this overrides the selection algorithm.
        if (SelectedGpuIndex.has_value()) {
            Log::Trace("Explicitly selecting GPU {}", SelectedGpuIndex.value());
            if (SelectedGpuIndex.value() > m_Gpus.size() - 1) {
                Log::Fatal({0x02, 0x09}, "Selected GPU index is out of bounds.");
            }
            return *m_Gpus[SelectedGpuIndex.value()];
        }

        // Find a discrete GPU
        for (const auto& gpu : m_Gpus) {
            if (gpu->GetProperties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                // See if it works with the surface
                const USize queueCount = gpu->GetQueueFamilyProperties().size();
                for (UInt32 queueIndex = 0; static_cast<USize>(queueIndex) < queueCount; queueIndex++) {
                    if (gpu->IsPresentSupported(surface, queueIndex)) {
                        return *gpu;
                    }
                }
            }
        }

        // Otherwise juste pick the first one
        Log::Warn("Couldn't find a discrete (dedicated) physical device, picking default GPU.");
        return *m_Gpus[0];
    }

    PhysicalDevice& Instance::GetFirstGpu() const {
        assert(!m_Gpus.empty() && "No physical devices were found on the system.");

        // Find a discrete GPU
        for (const auto& gpu : m_Gpus) {
            if (gpu->GetProperties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                return *gpu;
            }
        }

        // Otherwise, pick the first one
        Log::Warn("Couldn't find a discrete (dedicated) physical device, picking default GPU.");
        return *m_Gpus[0];
    }

    bool Instance::IsEnabled(const char* extension) {
        return std::ranges::find_if(m_EnabledExtensions, [extension](const char* enabledExtension) {
            return strcmp(enabledExtension, extension) == 0;
        }) != m_EnabledExtensions.end();
    }
}

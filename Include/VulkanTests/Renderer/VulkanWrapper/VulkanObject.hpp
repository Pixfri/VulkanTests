// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VULKANWRAPPER_VULKANOBJECT_HPP
#define VK_TESTS_RENDERER_VULKANWRAPPER_VULKANOBJECT_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/VkCommon.hpp>

#include <vulkan/vulkan.hpp>

#include <utility>

namespace VkTests {
    class Device;

    namespace Renderer {
        class HPPDevice;

        // Mapping from VkHandle type to vk::Handle type -> can be removed when it materializes in vulkan.hpp
        namespace Detail {
            template <typename HandleType>
            struct HPPType {
            };

            template <>
            struct HPPType<VkBuffer> {
                using Type = vk::Buffer;
            };

            template <>
            struct HPPType<VkCommandBuffer> {
                using Type = vk::CommandBuffer;
            };

            template <>
            struct HPPType<VkDevice> {
                using Type = vk::Device;
            };

            template <>
            struct HPPType<VkImage> {
                using Type = vk::Image;
            };

            template <>
            struct HPPType<VkImageView> {
                using Type = vk::ImageView;
            };

            template <>
            struct HPPType<VkRenderPass> {
                using Type = vk::RenderPass;
            };

            template <>
            struct HPPType<VkSampler> {
                using Type = vk::Sampler;
            };
        }

        /// Inherit this for any Vulkan object with a handle of type `HPPHandle`.
        ///
        /// This allows the derived class to store a Vulkan handle, and also a pointer to the parent device.
        /// It also allows to set a debug name for any Vulkan object.
        template <BindingType Binding, typename Handle>
        class VulkanObject {
        public:
            using DeviceType = std::conditional_t<Binding == BindingType::Cpp, HPPDevice, Device>;
            using ObjectType = std::conditional_t<Binding == BindingType::Cpp, vk::ObjectType, VkObjectType>;

            VulkanObject(Handle handle = nullptr, DeviceType* device = nullptr);
            virtual ~VulkanObject() = default;

            VulkanObject(const VulkanObject&) = delete;
            VulkanObject(VulkanObject&& other) noexcept;

            VulkanObject& operator=(const VulkanObject&) = delete;
            VulkanObject& operator=(VulkanObject&& other) noexcept;

            [[nodiscard]] const std::string& GetDebugName() const;
            DeviceType& GetDevice();
            const DeviceType& GetDevice() const;
            Handle& GetHandle();
            const Handle& GetHandle() const;
            [[nodiscard]] UInt64 GetHandleUInt64() const;
            ObjectType GetObjectType() const;
            [[nodiscard]] bool HasDevice() const;
            [[nodiscard]] bool HasHandle() const;
            void SetDebugName(std::string name);
            void SetHandle(Handle handle);

        private:
            // We always want to store a vk::Handle as a resource, so we have to figure out that type, depending on the BindingType.
            template <BindingType Bt, typename T>
            struct DetermineResourceType {
            };

            template <typename T>
            struct DetermineResourceType<BindingType::Cpp, T> {
                using Type = T;
            };

            template <typename T>
            struct DetermineResourceType<BindingType::C, T> {
                using Type = typename Detail::HPPType<T>::Type;
            };
            using ResourceType = typename DetermineResourceType<Binding, Handle>::Type;

            std::string m_DebugName;
            HPPDevice* m_Device;
            ResourceType m_Handle;
        };

        template <typename Handle>
        using VulkanObjectC = VulkanObject<BindingType::C, Handle>;
        template <typename Handle>
        using VulkanObjectCpp = VulkanObject<BindingType::Cpp, Handle>;
    }
}

#include <VulkanTests/Renderer/VulkanWrapper/VulkanObject.inl>

#endif // VK_TESTS_RENDERER_VULKANWRAPPER_VULKANOBJECT_HPP

// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::Renderer {
    template <BindingType Binding, typename Handle>
    VulkanObject<Binding, Handle>::VulkanObject(Handle handle, DeviceType* device) : m_Handle{handle} {
        if constexpr (Binding == BindingType::Cpp) {
            m_Device = device;
        } else {
            m_Device = reinterpret_cast<HPPDevice*>(device);
        }
    }

    template <BindingType Binding, typename Handle>
    VulkanObject<Binding, Handle>::VulkanObject(VulkanObject&& other) noexcept
        : m_DebugName(std::exchange(other.m_DebugName, {})),
          m_Device(std::exchange(other.m_Device, {})),
          m_Handle(std::exchange(other.m_Handle, {})) {
    }

    template <BindingType Binding, typename Handle>
    VulkanObject<Binding, Handle>& VulkanObject<Binding, Handle>::operator=(VulkanObject&& other) noexcept {
        m_DebugName = std::exchange(other.m_DebugName, {});
        m_Device = std::exchange(other.m_Device, {});
        m_Handle = std::exchange(other.m_Handle, {});

        return *this;
    }

    template <BindingType Binding, typename Handle>
    const std::string& VulkanObject<Binding, Handle>::GetDebugName() const {
        return m_DebugName;
    }

    template <BindingType Binding, typename Handle>
    typename VulkanObject<Binding, Handle>::DeviceType& VulkanObject<Binding, Handle>::GetDevice() {
        assert(m_Device && "Device handle not set.");
        if constexpr (Binding == BindingType::Cpp) {
            return *m_Device;
        }

        return *reinterpret_cast<Device*>(m_Device);
    }

    template <BindingType Binding, typename Handle>
    const typename VulkanObject<Binding, Handle>::DeviceType& VulkanObject<Binding, Handle>::GetDevice() const {
        assert(m_Device && "Device handle not set.");
        if constexpr (Binding == BindingType::Cpp) {
            return *m_Device;
        }

        return *reinterpret_cast<const Device*>(m_Device);
    }

    template <BindingType Binding, typename Handle>
    Handle& VulkanObject<Binding, Handle>::GetHandle() {
        if constexpr (Binding == BindingType::Cpp) {
            return m_Handle;
        }

        return *reinterpret_cast<typename ResourceType::NativeType*>(&m_Handle);
    }

    template <BindingType Binding, typename Handle>
    const Handle& VulkanObject<Binding, Handle>::GetHandle() const {
        if constexpr (Binding == BindingType::Cpp) {
            return m_Handle;
        }

        return *reinterpret_cast<typename ResourceType::NativeType const*>(&m_Handle);
    }

    template <BindingType Binding, typename Handle>
    UInt64 VulkanObject<Binding, Handle>::GetHandleUInt64() const {
        // See https://github.com/KhronosGroup/Vulkan-Docs/issues/368 .
        // Dispatchable and non-dispatchable handle types are *not* necessarily binary-compatible!
        // Non-dispatchable handles _might_ be only 32-bit long. This is because, on 32-bit machines, they might be a typedef to a 32-bit pointer.
        using UIntHandle = std::conditional_t<sizeof(ResourceType) == sizeof(UInt32), UInt32, UInt64>;
        return static_cast<UInt64>(*reinterpret_cast<UIntHandle const*>(&m_Handle));
    }

    template <BindingType Binding, typename Handle>
    typename VulkanObject<Binding, Handle>::ObjectType VulkanObject<Binding, Handle>::GetObjectType() const {
        if constexpr (Binding == BindingType::Cpp) {
            return ResourceType::objectType;
        }

        return static_cast<VkObjectType>(ResourceType::objectType);
    }


    template <BindingType Binding, typename Handle>
    bool VulkanObject<Binding, Handle>::HasDevice() const {
        return m_Device != nullptr;
    }

    template <BindingType Binding, typename Handle>
    bool VulkanObject<Binding, Handle>::HasHandle() const {
        return m_Handle != nullptr;
    }

    template <BindingType Binding, typename Handle>
    void VulkanObject<Binding, Handle>::SetDebugName(std::string name) {
        m_DebugName = std::move(name);

        if (m_Device && !m_DebugName.empty()) {
            GetDevice().GetDebugUtils().SetDebugName(GetDevice().GetHandle(), GetObjectType(), GetHandleUInt64(), m_DebugName.c_str());
        }
    }

    template <BindingType Binding, typename Handle>
    void VulkanObject<Binding, Handle>::SetHandle(Handle handle) {
        m_Handle = handle;
    }
}

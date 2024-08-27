// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_PLATFORM_CONTEXT_HPP
#define VK_TESTS_PLATFORM_CONTEXT_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
    class UnixPlatformContext;
    class WindowsPlatformContext;
    
    /**
     * @brief A platform context contains abstract platform specific operations
     */
    class PlatformContext {
        friend class UnixPlatformContext;
        friend class WindowsPlatformContext;
        
    public:
        virtual ~PlatformContext() = default;

        PlatformContext(const PlatformContext&) = delete;
        PlatformContext(PlatformContext&&) = delete;

        PlatformContext& operator=(const PlatformContext&) = delete;
        PlatformContext& operator=(PlatformContext&&) = delete;

        [[nodiscard]] inline virtual const std::vector<std::string>& Arguments() const;
        [[nodiscard]] inline virtual const std::string& ExternalStorageDirectory() const;
        [[nodiscard]] inline virtual const std::string& TempDirectory() const;

    protected:
        std::vector<std::string> m_Arguments;
        std::string m_ExternalStorageDirectory;
        std::string m_TempDirectory;

        PlatformContext() = default;
    };
}

#include <VulkanTests/Platform/Context.inl>

#endif // VK_TESTS_PLATFORM_CONTEXT_HPP

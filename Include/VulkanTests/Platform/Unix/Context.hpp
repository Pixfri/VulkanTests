// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_PLATFORM_UNIX_CONTEXT_HPP
#define VK_TESTS_PLATFORM_UNIX_CONTEXT_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Platform/Context.hpp>

namespace VkTests {
    /**
     * @brief Unix platform context
     *
     * @warning Use in extreme consequences, with code guarded by the VK_TEST_PLATFORM_UNIX define.
     */
    class UnixPlatformContext final : public PlatformContext {
    public:
        UnixPlatformContext(int argc, char** argv);
        ~UnixPlatformContext() override = default;

        UnixPlatformContext(const UnixPlatformContext&) = delete;
        UnixPlatformContext(UnixPlatformContext&&) = delete;

        UnixPlatformContext& operator=(const UnixPlatformContext&) = delete;
        UnixPlatformContext& operator=(UnixPlatformContext&&) = delete;
    };
}

#endif // VK_TESTS_PLATFORM_UNIX_CONTEXT_HPP

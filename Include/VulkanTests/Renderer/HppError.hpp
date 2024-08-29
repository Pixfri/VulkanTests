// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_HPPERROR_HPP
#define VK_TESTS_RENDERER_HPPERROR_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/Error.hpp>

#include <vulkan/vulkan.hpp>

namespace VkTests::Common {
    /**
     * @brief facade class around VkTests::VulkanException, providing a vulkan.hpp-based interface
     *
     * See vkb::VulkanException for documentation
     */
    class HPPVulkanException final : public VulkanException {
        explicit HPPVulkanException(vk::Result result, const std::string& message = "Vulkan error");
    };
}

#include <VulkanTests/Renderer/HppError.inl>

#endif // VK_TESTS_RENDERER_HPPERROR_HPP

// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_HPPSTRINGS_HPP
#define VK_TESTS_RENDERER_HPPSTRINGS_HPP

#include <VulkanTests/pch.hpp>

#include <vulkan/vulkan.hpp>

namespace VkTests::Common {
    /**
     * @brief Facade helper functions around the functions in Renderer/strings.hpp providing a vulkan.hpp-based interface. 
     */
    inline std::string ToString(const vk::Extent2D& extent);
}

#include <VulkanTests/Renderer/HppStrings.inl>

#endif // VK_TESTS_RENDERER_HPPSTRINGS_HPP

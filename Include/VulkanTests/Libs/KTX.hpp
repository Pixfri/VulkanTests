// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_LIBS_KTX_HPP
#define VK_TESTS_LIBS_KTX_HPP

#include <ktx.h>

namespace VkTests {
    inline ktxTexture* LoadTexture(const std::string& filename);
}

#include <VulkanTests/Libs/KTX.inl>

#endif // VK_TESTS_LIBS_KTX_HPP

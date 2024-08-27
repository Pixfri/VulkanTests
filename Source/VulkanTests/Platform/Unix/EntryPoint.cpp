// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Platform/EntryPoint.hpp>

#include <VulkanTests/Platform/Unix/Context.hpp>

std::unique_ptr<VkTests::PlatformContext> CreatePlatformContext(int argc, char** argv) {
    return std::make_unique<VkTests::UnixPlatformContext>(argc, argv);
}


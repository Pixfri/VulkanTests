// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Platform/EntryPoint.hpp>

#include <VulkanTests/Platform/Win32/Context.hpp>

std::unique_ptr<VkTests::PlatformContext> CreatePlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                                                                PSTR lpCmdLine, INT nCmdShow) {
	return std::make_unique<VkTests::WindowsPlatformContext>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

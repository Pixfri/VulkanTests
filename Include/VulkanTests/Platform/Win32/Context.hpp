// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_PLATFORM_WIN32_CONTEXT_HPP
#define VK_TESTS_PLATFORM_WIN32_CONTEXT_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Platform/Context.hpp>

#include <Windows.h>
#include <VulkanTests/Libs/AntiWindows.hpp>

namespace VkTests {
	/**
	 * @brief Windows platform context
	 *
	 * @warning Only use in extreme consequences, with code guarded by the VK_TESTS_PLATFORM_WINDOWS define.
	 */
	class WindowsPlatformContext final : public PlatformContext {
	public:
		WindowsPlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow);
		~WindowsPlatformContext() override = default;

		WindowsPlatformContext(const WindowsPlatformContext&) = delete;
		WindowsPlatformContext(WindowsPlatformContext&&) = delete;

		WindowsPlatformContext& operator=(const WindowsPlatformContext&) = delete;
		WindowsPlatformContext& operator=(WindowsPlatformContext&&) = delete;
	};
}

#endif // VK_TESTS_PLATFORM_WIN32_CONTEXT_HPP

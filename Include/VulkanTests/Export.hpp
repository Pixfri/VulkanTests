// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_EXPORT_HPP
#define VK_TESTS_EXPORT_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
	class Export {
	public:
		Export() = default;
		~Export() = default;

		Export(const Export&) = delete;
		Export(Export&&) = delete;

		Export& operator=(const Export&) = delete;
		Export& operator=(Export&&) = delete;

	private:
	};
}

#include <VulkanTests/Export.inl>

#endif // VK_TESTS_EXPORT_HPP

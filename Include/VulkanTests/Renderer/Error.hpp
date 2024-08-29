// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_ERROR_HPP
#define VK_TESTS_RENDERER_ERROR_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/VkCommon.hpp>

#include <VulkanTests/Core/Logger.hpp>

namespace VkTests {
	class VulkanException final : public std::runtime_error {
	public:
		explicit VulkanException(VkResult result, const std::string& message = "Vulkan error");

		/**
		 * @brief Returns the Vulkan error code as a string.
		 * @return String message of the exception.
		 */
		[[nodiscard]] inline const char* what() const noexcept override;

		VkResult Result;

	private:
		std::string m_ErrorMessage;
	};
}

#define VK_CHECK(x)                                                                       \
    do {                                                                                  \
        VkResult err = x;                                                                 \
        if (err)                                                                          \
            throw std::runtime_error("Vulkan error detected: " + VkTests::ToString(err)); \
        } \
    while (0)

#define ASSERT_VK_HANDLE(handle)                    \
    do {                                            \
        if ((handle) == VK_NULL_HANDLE) {           \
            VkTests::Log::Error("Handle is null."); \
            abort();                                \
        }                                           \
    } while (0);

#include <VulkanTests/Renderer/Error.inl>

#endif // VK_TESTS_RENDERER_ERROR_HPP

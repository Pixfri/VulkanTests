// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_UTILS_STRINGS_HPP
#define VK_TESTS_UTILS_STRINGS_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
	/**
	 * @brief Replaces all occurrences of a substring with another substring.
	 */
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

	/**
	 * @brief Removes all occurrences of a set of characters from the end of a string.
	 */
	std::string TrimRight(const std::string& str, const std::string& chars = "\t\n\v\f\r\b ");

	/**
	 * @brief Removes all occurrences of a set of characters from the beginning of a string.
	 */
	std::string TrimLeft(const std::string& str, const std::string& chars = "\t\n\v\f\r\b ");
}

#include <VulkanTests/Utils/Strings.inl>

#endif // VK_TESTS_UTILS_STRINGS_HPP

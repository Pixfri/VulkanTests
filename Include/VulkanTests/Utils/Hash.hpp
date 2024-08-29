// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_UTILS_HASH_HPP
#define VK_TESTS_UTILS_HASH_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
	inline void HashCombine(USize& seed, USize hash);

	/**
	 * @brief Helper function to combine a given hash
	 *        with a generated hash for the input param.
	 */
	template <class T>
	void HashCombine(USize& seed, const T& value);
}

#include <VulkanTests/Utils/Hash.inl>

#endif // VK_TESTS_UTILS_HASH_HPP

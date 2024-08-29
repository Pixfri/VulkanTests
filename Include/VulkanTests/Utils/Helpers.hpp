// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_UTILS_HELPERS_HPP
#define VK_TESTS_UTILS_HELPERS_HPP

#include <VulkanTests/pch.hpp>

#include <queue>
#include <set>
#include <sstream>

namespace VkTests {
	template <typename T>
	void Read(std::istringstream& is, T& value);

	template <typename T>
	void Read(std::istringstream& is, std::string& value);

	template <class T>
	void Read(std::istringstream& is, std::set<T>& value);

	template <class T>
	void Read(std::istringstream& is, std::vector<T>& value);

	template <class T, class S>
	void Read(std::istringstream& is, std::map<T, S>& value);

	template <class T, UInt32 N>
	void Read(std::istringstream& is, std::array<T, N>& value);

	template <typename T, typename... Args>
	void Read(std::istringstream& is, T& firstArg, Args&... args);

	template <typename T>
	void Write(std::ostringstream& os, const T& value);

	inline void Write(std::ostringstream& os, const std::string& value);

	template <class T>
	void Write(std::ostringstream& os, const std::set<T>& value);

	template <class T>
	void Write(std::ostringstream& os, const std::vector<T>& value);

	template <class T, class S>
	void Write(std::ostringstream& os, const std::map<T, S>& value);

	template <class T, UInt32 N>
	void Write(std::ostringstream& os, const std::array<T, N>& value);

	template <typename T, typename... Args>
	void Write(std::ostringstream& os, const T& firstArg, const Args&... args);

	/**
	 * @brief Helper function to convert a data type
	 *        to string using output stream operator.
	 * @param value The object to be converted to string
	 * @return String version of the given object
	 */
	template <class T>
	std::string ToString(const T& value);

	/**
	 * @brief Helper function to check size_t is correctly converted to uint32_t
	 * @param value Value of type size_t to convert
	 * @return An uint32_t representation of the same value
	 */
	template <class T>
	UInt32 ToUInt32(T value);

	template <typename T>
	std::vector<UInt8> ToBytes(const T& value);
}

#include <VulkanTests/Utils/Helpers.inl>

#endif // VK_TESTS_UTILS_HELPERS_HPP
